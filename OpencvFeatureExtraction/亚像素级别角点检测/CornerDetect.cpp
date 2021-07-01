#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat src, dst, src_gray;
const char *INPUT = "Input";
const char *OUTPUT = "Output";

int value = 10;
int valueMax = 20;

void SubPixel_Demo(int, void*);

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
	imshow(INPUT, src);

	cvtColor(src, src_gray, CV_BGR2GRAY);
	createTrackbar("Value:", OUTPUT, &value, valueMax, SubPixel_Demo);
	SubPixel_Demo(0, 0);
	waitKey(0);
	return 0;
}

void SubPixel_Demo(int, void*)
{
	if (value > 20)
		value = 20;
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	goodFeaturesToTrack(src_gray, corners, value, qualityLevel, minDistance, Mat(), blockSize, false);
	Mat resultImg = src.clone();
	for (size_t i = 0; i < corners.size(); i++)
	{
		circle(resultImg, corners[i], 10, Scalar(0, 0, 255), -1, 8);
	}
	imshow(OUTPUT, resultImg);

	Size winSize = Size(5, 5);
	Size zerozone = Size(-1, -1);
	TermCriteria tc = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
	cornerSubPix(src_gray, corners, winSize, zerozone, tc);
	for (size_t t = 0; t < corners.size(); t++)
	{
		cout << (t + 1) << ".Point(X,Y)" << corners[t].x << "," << corners[t].y << endl;
	}
}


