// Test_imgOperate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void MyLine(Mat src);
void MyRectangle(Mat src);
void MyEllipse(Mat src);
void MyCircle(Mat src);
void MyPolygon(Mat src);//多边形
void MyRandomLineDemo(Mat src);

int main()
{	/* 简单图像混合 */
	//Mat pic1 = imread("pic.jpg");
	//Mat pic2 = imread("pic1.jpg");
	//Mat dst;
	//double alpha = 0.5;
	//if ((pic1.data || pic2.data) == NULL)
	//{
	//	cout << "could not load img..." << endl;
	//}
	//if (pic1.size() == pic2.size()
	//	&& pic1.type() == pic2.type())
	//{
	//	addWeighted(pic1, alpha, pic2, 1 - alpha, 0, dst);//线性混合—线性函数
	//	//multiply(pic1, pic2, dst, 1);//乘法
	//}
	//else cout << "img not equal" << endl;
	/*  提高亮度和对比度  */
	//Mat src, dst;
	//src = imread("pic.jpg");
	//if (src.data == NULL)
	//{
	//	cout << "could not imread img ..." << endl;
	//}
	//char input[] = "img Ouput";
	//namedWindow(input, CV_WINDOW_AUTOSIZE);
	//imshow(input, src);

	//int width = src.cols;
	//int heigh = src.rows;

	//float alpha = 1.3;
	//float beta = 30;

	//dst = Mat::zeros(src.size(), src.type());
	//for (int row = 0; row < heigh; row++)
	//{
	//	for (int col = 0; col < width; col++)
	//	{
	//		if (src.channels() == 1)
	//		{//单通道
	//			float v = src.at<uchar>(row, col);
	//			dst.at<uchar>(row, col) = saturate_cast<uchar>(v*alpha + beta);
	//		}
	//		else if (src.channels() == 3)
	//		{//三通道
	//			float b = src.at<Vec3b>(row, col)[0];
	//			float g = src.at<Vec3b>(row, col)[1];
	//			float r = src.at<Vec3b>(row, col)[2];
	//			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha + beta);
	//			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
	//			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);

	//		}
	//		else
	//		{
	//			cout << "could solve this type" << endl;
	//		}
	//	}
	//}
	//char output[] = "constract and brightness change img";
	//namedWindow(output, CV_WINDOW_AUTOSIZE);
	//imshow(output, dst);

	/*  绘制形状文字  */
	Mat src, dst;
	src = imread("pic.jpg");
	if (src.data == NULL)
	{
		cout << "could not imread img ..." << endl;
	}
	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	//MyLine(src);
	//MyRectangle(src);
	//MyEllipse(src);
	//MyCircle(src);
	//MyPolygon(src);
	//putText(src, "HelloWorld", Point(src.rows / 2, src.cols / 2), CV_FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 255, 255), 2, LINE_AA);
	MyRandomLineDemo(src);
	imshow("Output", src);
	waitKey(0);
}

void MyLine(Mat src)
{
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 200;
	p2.y = 300;
	Scalar color = Scalar(255, 0, 0);
	line(src, p1, p2, color, 1, LINE_AA);//使用反锯齿较其他更耗性能
}

void MyRectangle(Mat src)
{
	Rect rect = Rect(200, 100, 100, 100);
	Scalar color = Scalar(0, 255, 0);
	rectangle(src, rect, color, 3, LINE_8);
}

void MyEllipse(Mat src)
{
	Scalar color = Scalar(0, 0, 255);
	ellipse(src,Point(src.cols/2,src.rows/2-50),Size(src.cols / 4, src.rows / 8),90,0,360,color,2,LINE_AA);//（背景，圆心，圆半径，倾斜角度，开始角度，结束角度，颜色，线粗，线形）
}

void MyCircle(Mat src)
{
	Scalar color = Scalar(255, 0, 255);
	circle(src, Point(src.cols / 2+100, src.rows / 2), 50, color, 2, LINE_AA);
}

void MyPolygon(Mat src)
{
	Point pts[1][5];
	pts[0][0] = Point(100, 100);
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 200);
	pts[0][3] = Point(200, 100);
	pts[0][4] = Point(250, 150);

	const Point*ppts[] = {pts[0]};
	int npt[] = { 5 };
	Scalar color = Scalar(0, 255, 255);
	fillPoly(src, ppts, npt, 1, color, 8);
}

void MyRandomLineDemo(Mat src)
{
	RNG rng(12345);
	Point pt1;
	Point pt2;
	pt1.x = rng.uniform(0,src.cols);
	pt2.x = rng.uniform(0, src.cols);
	pt1.y = rng.uniform(0, src.rows);
	pt2.y = rng.uniform(0, src.rows);

	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	line(src, pt1, pt2, color, 3, 8);

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
