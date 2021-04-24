// Test_Install.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include<iostream>  
#include <opencv2/core/core.hpp> 
#include<opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>  
using namespace cv;
int main()
{
	// 读入一张图片
	Mat img = imread("pic.jpg");
	// 创建一个名为 "游戏原画"窗口  
	cvNamedWindow("游戏原画");
	// 在窗口中显示游戏原画  
	imshow("游戏原画", img);
	// 等待1000 ms后窗口自动关闭  
	waitKey(1000);
	//创建一个新的图像为img_grey，色彩空间转换
	Mat img_grey;
	cvtColor(img, img_grey, COLOR_BGR2GRAY);
	//保存图片
	imwrite("new_pic.jpg", img_grey);
	imshow("游戏原画", img_grey);
	waitKey(3000);

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
