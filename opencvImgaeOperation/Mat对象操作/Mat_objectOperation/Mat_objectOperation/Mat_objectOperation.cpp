// Mat_objectOperation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv.hpp>
using namespace cv;
using namespace std;

//int main()
//{//对Mat对象的操作
//	Mat src;
//	src = imread("pic.jpg");
//	if (src.empty())
//	{
//		cout << "could not load Image..." << endl;
//		return -1;
//	}
//	namedWindow("input", CV_WINDOW_AUTOSIZE);
//	imshow("input", src);
//
//	////Mat构造
//	//Mat dst;
//	//dst = Mat(src.size(), src.type());
//	//dst = Scalar(127, 0, 255);//整张图染成一个色
//
//	//Mat克隆
//	//Mat dst = src.clone();
//	//Mat_copyTo
//
//	/*Mat dst;
//	src.copyTo(dst);
//	cvtColor_色彩空间转换
//	cvtColor(src, dst, CV_BGR2GRAY);*/
//
//	//printf("input image channels:%d\n", src.channels());
//	//printf("output image channels:%d\n", dst.channels());
//
//	//const uchar* first_Row = dst.ptr<uchar>(0);
//	//printf("The image Fist_Row:%d\n", *first_Row);
//
//	//int cols = dst.cols;
//	//int rows = dst.rows;
//
//	//Mat dst(3, 3, CV_8UC3, (0, 0, 255));
//
//	//Scalar
//	/*Mat dst;
//	dst.create(src.size(), src.type());
//	dst = Scalar(0.20, 55);*/
//
//	/*Mat dst;
//	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//	filter2D(src, dst, src.depth(), kernel);*/
//
//	//namedWindow("output", CV_WINDOW_AUTOSIZE);
//	//imshow("output", dst);
//
//	waitKey(0);
//}

int main()
{//对图像的处理
	Mat src = imread("pic.jpg");
	if (src.empty())
	{
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	//Mat src_gray;
	//cvtColor(src, src_gray, CV_BGR2GRAY);

	//int width = src_gray.rows;
	//int heigh = src_gray.cols;

	//for (int i = 0; i < width; i++)
	//{
	//	for (int j = 0; j < heigh; j++)
	//	{
	//		int gray = src_gray.at<uchar>(i,j);
	//		src_gray.at<uchar>(i, j) = 255 - gray;
	//	}
	//}

	//三通道
	Mat dst;
	dst.create(src.size(), src.type());
	int width = dst.rows;
	int heigh = dst.cols;
	int Ch = dst.channels();
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigh; j++)
		{
			int Opsite1 = src.at<Vec3b>(i,j)[0];
			int Opsite2 = src.at<Vec3b>(i, j)[1];
			int Opsite3 = src.at<Vec3b>(i, j)[2];
			dst.at<Vec3b>(i, j)[0] = 255 - Opsite1;
			dst.at<Vec3b>(i, j)[1] = 255 - Opsite2;
			dst.at<Vec3b>(i, j)[2] = 255 - Opsite3;
		}
	}
	/*Mat dst;
	dst.create(src.size(), src.type());
	bitwise_not(src, dst);*/

	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);

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
