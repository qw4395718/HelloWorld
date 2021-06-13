#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, src_gray, dst;
RNG rng;

const char *INPUT = "Input image";
const char *OUTPUT = "Output image";
int thresholdValue = 100;
int thresholdMax = 255;

void ContoursCallBack(int, void*);
int main()
{
	src = imread("Mario.jpg");
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

	createTrackbar("Value", OUTPUT, &thresholdValue, thresholdMax, ContoursCallBack);
	ContoursCallBack(0, 0);

	waitKey(0);
	return 0;
}
void ContoursCallBack(int, void*)
{
	Mat binary_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;

	threshold(src_gray, binary_output, thresholdValue, thresholdMax, THRESH_BINARY);
	findContours(binary_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));
	vector<vector<Point>> contoursPloy(contours.size());//轮廓外界多边形
	vector<Rect>ployRect(contours.size());
	vector<Point2f>ccs(contours.size());
	vector<float>radius(contours.size());

	vector<RotatedRect> minRects(contours.size());
	vector<RotatedRect> myellipse(contours.size());

	src.copyTo(dst);

	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(contours[i], contoursPloy[i], 3, true);
		ployRect[i] = boundingRect(contoursPloy[i]);
		minEnclosingCircle(contoursPloy[i], ccs[i], radius[i]);

	}
	for (size_t j = 0; j < contoursPloy.size(); j++)
	{
		rectangle(dst,ployRect[j],Scalar(0,255,0),2,8);
		circle(dst, ccs[j], radius[j], Scalar(255, 0, 0), 2, 8);
		
	}
	imshow(OUTPUT, dst);
}