#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const char* INPUT = "Input";
const char* OUTPUT = "Output";

int thresholdValue = 100;
int thresholdMax = 255;

RNG rng;
Mat src,src_gray, dst;
void Demo_Pointtest(int, void*);
int main()
{
	const int r = 100;
	Mat src = Mat::zeros(r * 4, r * 4, CV_8UC1);

	vector<Point2f>vert(6);
	vert[0] = Point(3 * r / 2, static_cast<int>(1.34*r));
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(3 * r / 2, static_cast<int>(2.86*r));
	vert[3] = Point(5 * r / 2, static_cast<int>(2.86*r));
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(5 * r / 2, static_cast<int>(1.34*r));

	for (size_t i = 0; i < 6; i++)
	{
		line(src, vert[i], vert[(i + 1) % 6], Scalar(255), 3, 8, 0);
	}

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	Mat csrc;
	src.copyTo(csrc);
	findContours(csrc, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat raw_dist = Mat::zeros(csrc.size(), CV_32FC1);
	for (int row = 0; row < raw_dist.rows; row++)
	{
		for (int col = 0; col < raw_dist.cols; col++)
		{
			double dist = pointPolygonTest(contours[0], Point2f(static_cast<float>(col), static_cast<float>(row)), true);
			raw_dist.at<float>(row, col) = static_cast<float>(dist);
		}
	}

	double minValue, maxValue;
	minMaxLoc(raw_dist, &minValue, &maxValue, 0, 0, Mat());
	Mat drawImg = Mat::zeros(csrc.size(), CV_8UC3);
	for (int row = 0; row < drawImg.rows; row++)
	{
		for (int col = 0; col < drawImg.cols; col++)
		{
			double dist = raw_dist.at<float>(row, col);
			if (dist > 0)
			{
				drawImg.at<Vec3b>(row, col)[0] = (uchar)(abs(dist / maxValue) * 255);
			}
			else if (dist < 0)
			{
				drawImg.at<Vec3b>(row, col)[2] = (uchar)(abs(dist / minValue) * 255);
			}
			else
			{
				drawImg.at<Vec3b>(row, col)[0] = (uchar)(abs(255 - dist));
				drawImg.at<Vec3b>(row, col)[1] = (uchar)(abs(255 - dist));
				drawImg.at<Vec3b>(row, col)[2] = (uchar)(abs(255 - dist));
			}
		}
	}

	imshow(OUTPUT, drawImg);

	waitKey(0);
	return 0;
}

//void Demo_Pointtest(int, void *)
//{
//	vector<vector<Point>> contours;
//	vector<Vec4i> heirarchy;
//	Mat drawImg = Mat::zeros(400, 400,CV_8UC1);
//	findContours(src_gray, contours, heirarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	for (size_t i = 1; i < contours.size(); i++)
//	{
//
//	}
//
//}