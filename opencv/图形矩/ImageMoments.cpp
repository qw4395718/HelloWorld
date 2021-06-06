#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, src_gray, dst;
const char* INPUT = "Input";
const char* OUTPUT = "Output"; 
int thresholdValue = 100;
int thresholdMax = 255;
RNG rng;

void Demo_Moments(int, void*);

int main()
{
	src = imread("circle.jpg");
	if (src.empty())
	{
		cout << "could not load img ..." << endl;
		return -1;
	}
	namedWindow(INPUT, CV_WINDOW_NORMAL);
	namedWindow(OUTPUT, CV_WINDOW_NORMAL);
	imshow(INPUT, src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	createTrackbar("ThresholdValue", OUTPUT, &thresholdValue, thresholdMax, Demo_Moments);
	Demo_Moments(0, 0);


	waitKey(0);
	return 0;
}

void Demo_Moments(int, void*)
{
	Mat cannyImg;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	Canny(src_gray, cannyImg, thresholdValue, thresholdValue * 2, 3, false);
	findContours(cannyImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> contours_moments(contours.size());
	vector<Point2f> ccs(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		contours_moments[i] = moments(contours[i]);
		ccs[i] = Point(static_cast<float>(contours_moments[i].m10 / contours_moments[i].m00), static_cast<float>(contours_moments[i].m01 / contours_moments[i].m00));
	}
	Mat drawImg;
	src.copyTo(drawImg);
	rng(12345);
	for (size_t j = 0; j < contours.size(); j++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		printf("contours %d area: %.2f  arc length: %.2f\n", j, contourArea(contours[j], false),arcLength(contours[j],true));
		drawContours(drawImg, contours, j, color, 1, LINE_AA, hieracy, 0, Point(0, 0));
		circle(drawImg, ccs[j], 1, color, 2, 8);
	}
	imshow(OUTPUT, drawImg);

}