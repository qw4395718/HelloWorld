#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat src, src_gray, dst;

const char* INPUT = "INPUT";
const char* OUTPUT = "OUTPUT";

int main(void)
{
	src = imread("source.jpg");
	if (src.empty())
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	namedWindow(INPUT);
	namedWindow(OUTPUT);

	//change write backgroud to black
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			if (Vec3b(255,255,255) == src.at<Vec3b>(row, col))
			{
				src.at<Vec3b>(row, col)[0] = 0;
				src.at<Vec3b>(row, col)[1] = 0;
				src.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	imshow(INPUT, src);
	//sharp
	Mat Kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	Mat src_laplacian;
	Mat sharpImg;
	src.convertTo(sharpImg,CV_32F);
	filter2D(src, src_laplacian, CV_32F, Kernel, Point(-1, -1), 0, BORDER_DEFAULT);//CV_32F可以应付出现负数的结果
	Mat resultImg = sharpImg - src_laplacian;
	resultImg.convertTo(resultImg,CV_8UC3);
	src_laplacian.convertTo(src_laplacian, CV_8UC3);
	imshow("sharp image", resultImg);

	//二值图像变换
	Mat thresholdImg;
	cvtColor(resultImg, src_gray, CV_BGR2GRAY);
	threshold(src_gray, thresholdImg, 40, 255, THRESH_BINARY|THRESH_OTSU);
	imshow(OUTPUT, thresholdImg);

	//距离变换
	Mat disImg;
	distanceTransform(thresholdImg, disImg, DIST_L1, 3);
	normalize(disImg, disImg, 0, 1, NORM_MINMAX);
	imshow("Normalize img", disImg);

	// 二值处理
	threshold(disImg, disImg, 0.1, 1, THRESH_BINARY);
	imshow("Binary img", disImg);

	//erode和dilate
	Mat kernel = Mat::ones(2, 2, CV_8UC1);
	erode(disImg, disImg, kernel, Point(-1, -1));
	imshow("Erode img", disImg);

	//markers
	Mat dist_8u;
	disImg.convertTo(dist_8u, CV_8U);
	vector<vector<Point>> contours;
	findContours(dist_8u, contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(0,0));

	//create contours
	Mat markers = Mat::zeros(disImg.size(), CV_32SC1);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+ 1),-1);//thickness =-1 表示填充

	}

	circle(markers, Point(5, 5), 3, Scalar(255, 255, 255), -1);//thickness =-1 表示填充
	imshow("Markers", markers*1000);

	//water
	watershed(resultImg, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark, Mat());
	imshow("water", mark);

	//color block
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++)
	{
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)r, (uchar)g, (uchar)b));
	}

	//fill with color by result
	dst = Mat::zeros(mark.size(), CV_8UC3);
	for (int row = 0; row < dst.rows; row++)
	{
		for (int col = 0; col < dst.cols; col++)
		{
			int index = markers.at<int>(row, col);
			if (index > 0 && index <= static_cast<int>(contours.size()))
			{
				dst.at<Vec3b>(row, col) = colors[index - 1];
			}
			else
			{
				dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow(OUTPUT, dst);

	waitKey(0);
	return 0;
}