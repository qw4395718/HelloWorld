#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat harris_dst, harrisRspImg;
Mat src, dst, src_gray;
double harris_min;
double harris_max;
int qualityLevel=30;
int qualityMax = 100;

const char *INPUT = "Input";
const char *OUTPUT = "Output";

const char* harrisWindow = "Custom Harris Comers Detector";

void CustomHarris_Demo(int, void*);

int main(void)
{
	src = imread("pic_JK.jpg");
	if (src.empty())
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(harrisWindow, CV_WINDOW_AUTOSIZE);

	imshow(INPUT, src);

	cvtColor(src, src_gray, CV_RGB2GRAY);

	//计算特征值
	int blockSize = 2;
	int ksize = 3;
	double k = 0.04;

	harrisRspImg = Mat::zeros(src.size(), CV_32FC1);
	harris_dst = Mat::zeros(src.size(), CV_32FC(6));
	cornerEigenValsAndVecs(src_gray, harris_dst,blockSize,ksize,4);

	//计算响应

	for (int row = 0; row < harris_dst.rows; row++)
	{
		for (int col = 0; col < harris_dst.cols; col++)
		{
			double lambda1 = harris_dst.at<Vec6f>(row, col)[0];
			double lambda2 = harris_dst.at<Vec6f>(row, col)[1];
			harrisRspImg.at<float>(row, col) = lambda1 * lambda2 - k * pow((lambda1 + lambda2),2);

		}
	}
	

	minMaxLoc(harrisRspImg, &harris_min, &harris_max, 0, 0, Mat());
	createTrackbar("Quality Value:",harrisWindow,&qualityLevel, qualityMax,CustomHarris_Demo);

	CustomHarris_Demo(0, 0);

	waitKey(0);
	return 0;
}
void CustomHarris_Demo(int, void*)
{
	if (qualityLevel < 10)
	{
		qualityLevel = 10;
	}
	Mat resultImg = src.clone();
	float t = harris_min + (((double)qualityLevel / qualityMax)*(harris_max - harris_min));
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			float v = harrisRspImg.at<float>(row, col);
			if (v > t) {
				circle(resultImg, Point(col, row), 2, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}
	imshow(harrisWindow, resultImg);
}