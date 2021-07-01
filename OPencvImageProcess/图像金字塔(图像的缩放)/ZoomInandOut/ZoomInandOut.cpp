// ZoomInandOut.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//#define UnitTest1
#define UnitTest2

int main()
{
	Mat src;
	src = imread("pic_JK.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", src);

#ifdef UnitTest1
	 /* 高斯金字塔 
	  *第一步：进行高斯模糊
	  *第二步，删除偶数行和列
	  *第三步，重复一二步直到图片达到指定要求*/
	Mat dst;
	//pyrUp(src,dst,Size(src.cols*2,src.rows*2));//上采样
	for(int i =0;i<5;i++)
	{
		pyrDown(src, src, Size(src.cols / 2, src.rows / 2));//降采样
		cvtColor(src, src,CV_RGB2GRAY);

	}
	imshow("Output", src);
#endif

#ifdef UnitTest2
	/* DOG */
	Mat src_gray, g1, g2, dogimg;
	cvtColor(src, src_gray, CV_RGB2GRAY);
	GaussianBlur(src_gray, g1, Size(3, 3), 0, 0);
	GaussianBlur(g1, g2, Size(3, 3), 0,0);
	subtract(g1, g2, dogimg, Mat());
	//归一化显示
	normalize(dogimg, dogimg, 255, 0,NORM_MINMAX);
	imshow("Output", dogimg);
#endif
	waitKey(0);
	return 0;

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
