#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
/*
*凸包:包含n个点的最小凸多边形
*/
using namespace std;
using namespace cv;

Mat src, src_gray, dst;
RNG rng;

const char *INPUT = "Input image";
const char *OUTPUT = "Output image";
int thresholdValue = 100;
int thresholdMax = 255;

void ThresholdCallBack(int, void*);
int main()
{
	src = imread("ColorfulFish.jpg");
	if (!src.data)
	{
		cout << "Could not load img..." << endl;
		return -1;
	}
	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_NORMAL);
	imshow(INPUT, src);

	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);

	createTrackbar("Threshold", OUTPUT, &thresholdValue, thresholdMax, ThresholdCallBack);
	ThresholdCallBack(0, 0);

	waitKey(0);
	return 0;
}

void ThresholdCallBack(int, void*)
{
	Mat src_threshold;
	vector<vector<Point>> contoursPoint;
	vector<Vec4i> hierachy;
	rng(12345);

	threshold(src_gray, src_threshold, thresholdValue, thresholdMax, THRESH_BINARY);
	findContours(src_threshold, contoursPoint, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> convexhulls(contoursPoint.size());
	for (size_t i = 1; i < contoursPoint.size(); i++)
	{
		convexHull(contoursPoint[i], convexhulls[i], false, true);
	}


	dst = Mat::zeros(src.size(), CV_8UC3);
	for (size_t j; j < contoursPoint.size(); j++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contoursPoint, j, color, 2, LINE_AA, hierachy, 0, Point(0, 0));
		drawContours(dst, convexhulls, j, color, 2, LINE_AA, Mat(), 0, Point(0, 0));
	}
	imshow(OUTPUT, dst);
}