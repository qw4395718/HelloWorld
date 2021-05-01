// ImgExpendandRust.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WK_TRUE 1
#define WK_FALSE 0
#define WK_ERROR -1

int main()
{
	Mat src, dst, src_gray;
	src = imread("pic.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	dst = Mat::zeros(src.size(), src.type());
	char Input[] = "original img";
	char Output[] = "operate img";
	namedWindow(Input, CV_WINDOW_AUTOSIZE);
	namedWindow(Output, CV_WINDOW_AUTOSIZE);
	//灰度处理

	if (src.channels() == 3)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	//cout << dst.channels() << endl;
	//Mat Kernel = getStructuringElement(MORPH_RECT,Size(5,5),Point(-1,-1));//存在问题？Size在操作中发挥什么作用
	//erode(src, src, Kernel);//腐蚀操作

	adaptiveThreshold(~src_gray, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);

	imshow(Input, src);
	imshow(Output, dst);
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
