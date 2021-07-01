#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat src, dst, src_gray;
const char *INPUT = "Input";
const char *OUTPUT = "Output";
int thresholdValue = 130;
int thresholdMax = 255;

void HarrisDemo(int, void*);
int main(void )
{
	src = imread("pic.jpg");
	if (src.empty())
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);
	imshow(INPUT, src);

	cvtColor(src, src_gray,CV_BGR2GRAY);
	createTrackbar("Harris", OUTPUT, &thresholdValue, thresholdMax, HarrisDemo);
	HarrisDemo(0, 0);

	waitKey(0);
	return 0;
}

void HarrisDemo(int, void*)
{
	dst = Mat::zeros(src_gray.size(), CV_32FC1);

	Mat dst_result;
	int blockSize = 2;
	int kSize = 3;
	double k = 0.04;
	cornerHarris(src_gray, dst, blockSize, kSize, k);
	normalize(dst, dst, 0, 255, NORM_MINMAX,CV_32FC1, Mat());
	convertScaleAbs(dst, dst);

	dst_result = src.clone();
	for (int row = 0; row < dst_result.rows; row++)
	{
		uchar* pCurrentRow = dst.ptr(row);
		for (int col = 0; col < dst_result.cols; col++)
		{
			if (pCurrentRow[col] > thresholdValue)
			{
				circle(dst_result, Point(row, col), 2, Scalar(0.255, 0),2,8);
			}
		}
	}
	imshow(OUTPUT, dst_result);

	
}