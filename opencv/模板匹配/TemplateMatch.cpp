#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat m_src, m_hsv, m_hue;

char INPUT[] = "Input";
char OUTPUT[] = "Output";

int main()
{
	m_src = imread("pic_JK.jpg");

	if (!m_src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}

	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);
	imshow(INPUT, m_src);


	waitKey(0);
	return 0;
}