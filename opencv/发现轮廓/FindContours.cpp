#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat src, src_gray, dst;

const char *INPUT = "Input image";
const char *OUTPUT = "Output image";
int thresholdValue = 100;
int thresholdMax = 255;
RNG rng;

void FindContours(int, void*);

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
	createTrackbar("FC:", OUTPUT, &thresholdValue, thresholdMax, FindContours);
	FindContours(0, 0);

	waitKey(0);
	return 0;
}

void FindContours(int, void *)
{
	Mat cannyOutput;
	vector<vector<Point>> contourPoint;
	vector<Vec4i> hierachy;

	Canny(src_gray, cannyOutput, thresholdValue, thresholdValue * 2, 3, false);//flase 选择绝对值归一化方法
	findContours(cannyOutput, contourPoint, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	dst = Mat::zeros(src.size(), CV_8UC3);
	rng(12345);
	for(size_t i =0;i< contourPoint.size();i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contourPoint, i, color, 2, LINE_AA, hierachy, 0, Point(0, 0));
	}
	imshow(OUTPUT, dst);

}