// Morphology_Operate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
//#define UnitTest1
#define UnitTest2

int main()
{
#ifdef UnitTest1
	//第一单元测试
	Mat src, src_dilate,src_erode,src_open,src_close, src_gradient, src_TopHat, src_BlackHat;
	//src = imread("src_Morphology.png");
	//src = imread("src_Morphology_Close.png");
	src = imread("pic_JK.jpg");
	if (!src.data)
	{
		cout << "could not load img ..." << endl;
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	Mat Kernel = getStructuringElement(MORPH_RECT,Size(10,10),Point(-1,-1));
	/* open */
	//morphologyEx(src, src_open, CV_MOP_OPEN, Kernel, Point(-1, -1));//开操作的效果主要受到Kernel大小的影响，可以去掉小的对象，假设对象是前景色，背景是黑色
	//imshow("Input", src);
	//imshow("Output", src_open);

	/* close *///要想使用形态学操作需要先将图像进行二值处理灰度处理等处理
	//morphologyEx(src, src_close, CV_MOP_CLOSE, Kernel, Point(-1, -1));//可以填补小的洞，假设对象是前景色，背景是黑色
	//imshow("Input", src);
	//imshow("Output", src_close);

	/* Gradient */
	//morphologyEx(src, src_gradient, CV_MOP_GRADIENT, Kernel, Point(-1, -1));
	//imshow("Input", src);
	//imshow("Output", src_gradient);

	/* Top_Hat */
	//morphologyEx(src, src_gradient, CV_MOP_TOPHAT, Kernel, Point(-1, -1));//顶帽是原图像和开操作的差值图像
	//imshow("Input", src);
	//imshow("Output", src_TopHat);

	/* Black_Hat */
	//morphologyEx(src, src_gradient, CV_MOP_BALCK, Kernel, Point(-1, -1));//黑帽是原图像与闭操作的差值图像
	//imshow("Input", src);
	//imshow("Output", src_BlackHat);

#endif

#ifdef UnitTest2
	/*第二单元测试*/
	Mat src, dst,src_gray, src_binary,src_erode,src_dilate;
	src = imread("Morphology_test2.png");
	if (!src.data)
	{
		cout << "could not load img ..." << endl;
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(10, 10), Point(-1, -1));

	/*  提取水平与垂直直线 */
	//灰度处理
	cvtColor(src, src_gray, CV_BGR2GRAY);
	//二值图像，要二值先要灰度处理
	adaptiveThreshold(~src_gray, src_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	imshow("Input", src_binary);
	Mat hline = getStructuringElement(MORPH_RECT, Size(src_binary.cols / 16, 1), Point(-1, -1));
	Mat vline = getStructuringElement(MORPH_RECT, Size(1, src_binary.rows/16), Point(-1, -1));
	//开操作的另一种处理方式：erode（）+ dilate()
	//闭操作的另一种处理方式：dilate() + erode()
	erode(src_binary, src_erode, hline);
	dilate(src_erode, src_dilate, hline);
	bitwise_not(src_dilate, dst);
	imshow("Output", dst);


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
