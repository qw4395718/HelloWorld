// VagueOperate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define blur2 

int main()
{
	Mat src, dst;
	src = imread("zaosheng.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", src);
#ifdef blur1
	/* 均值模糊 */
	Mat dst_blur, dst_Gaussblur;
	//blur(src, dst_blur, Size(5, 5), Point(-1, -1));//size影响模糊的方向（X轴模糊，中心模糊，Y轴模糊）
	GaussianBlur(src, dst_blur, Size(29, 29), 5, 5);//Size影响模糊的程度，正态分布的加权均值相较均值模糊更清晰（X轴模糊，中心模糊，Y轴模糊）
	char Output1[] = "Img_blur";
	namedWindow(Output1, CV_WINDOW_AUTOSIZE);
	imshow(Output1, dst_blur);
	/* 高斯模糊 */
	GaussianBlur(src, dst_Gaussblur, Size(29, 29), 50000, 5);//sigmaX和sigmaY直观上影响（X轴模糊和Y轴模糊）
	char Output2[] = "Img_Gaussblur";
	namedWindow(Output2, CV_WINDOW_AUTOSIZE);
	imshow(Output2, dst_Gaussblur);
#endif

#ifdef blur2
	/* 中值模糊滤波 */
	//中值滤波一般用于处理椒盐噪声，即像素点相差较大的点
	/*medianBlur(src, dst,3);
	char Img_median[] = "Img_median";
	namedWindow(Img_median, CV_WINDOW_AUTOSIZE);
	imshow(Img_median, dst);*/
	/* 双边滤波 */
	//双边滤波一般用于特定区间的模糊，通过限定模糊范围从而可以保留边缘的清晰度
	bilateralFilter(src,dst,15,100,3);
	Mat Kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst, dst, -1, Kernel, Point(-1, -1), 0);
	char Img_median[] = "Img_bilaterafile";
	namedWindow(Img_median, CV_WINDOW_AUTOSIZE);
	imshow(Img_median, dst);
#endif
	waitKey(0);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
