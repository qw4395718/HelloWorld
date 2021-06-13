#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat m_src, m_hsv, m_hue;

char INPUT[] = "Input";
char OUTPUT[] = "Output";
const char* bar = { INPUT };
int bin = 10;

void HistBackProjection(int, void*);

int main()
{
	m_src = imread("pic_JK.jpg");

	if (!m_src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}

	namedWindow(INPUT,CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);

	cvtColor(m_src, m_hsv, CV_BGR2HSV);
	m_hue.create(m_hsv.size(), m_hsv.depth());
	int nchannels[] = { 0,0 };
	mixChannels(&m_hsv, 1, &m_hue, 1, nchannels,1);//将hsv的第一通道值赋予hue的第一通道
	
	createTrackbar("bin number:", bar, &bin, 180, HistBackProjection);
	HistBackProjection(0, 0);

	imshow(bar, m_src);
	waitKey(0);
	return 0;
}

void HistBackProjection(int, void*)
{
	float range[] = { 0,180 };
	const float *histRange = { range };
	Mat h_hist;
	calcHist(&m_hue, 1, 0, Mat(), h_hist,1, &bin, &histRange, true, false);
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX, -1, Mat());

	Mat backProjection;
	calcBackProject(&m_hue, 1, 0, h_hist, backProjection, &histRange, 1);
	imshow("BackProjection", backProjection);

	int hist_h = 400;
	int hist_w = 400;
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	int bin_w = hist_w / bin;


	for (int i = 1; i < bin; i++)
	{
		rectangle(histImage, Point((i - 1)*bin_w, cvRound(hist_h - h_hist.at<float>(i - 1)*(400 / 256))), Point((i)*bin_w, cvRound(hist_h - h_hist.at<float>(i)*(400 / 256))), Scalar(0, 255, 0), -1);
	}
	imshow(OUTPUT, histImage);
}
