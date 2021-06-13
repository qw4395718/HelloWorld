#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat m_src, m_dst,m_temple;

int match_method = CV_TM_SQDIFF;
int max_track = 5;
const char* INPUT = "Input";
const char* OUTPUT = "Output";
const char* TEMPLE = "Temple";

void Template_Match(int, void*);
int main()
{
	m_src = imread("Mario.jpg");
	m_temple = imread("MarioCoin.jpg");
	if (!m_src.data||!m_temple.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}

	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(TEMPLE, CV_WINDOW_AUTOSIZE);
	imshow(INPUT, m_src);
	imshow(TEMPLE, m_temple);

	const char* trackbar_title = "Match means type:";
	createTrackbar(trackbar_title, OUTPUT, &match_method, max_track, Template_Match);
	Template_Match(0, 0);

	waitKey(0);
	return 0;
}

void Template_Match(int, void*)
{
	int width = m_src.cols - m_temple.cols + 1;
	int height = m_src.rows - m_temple.rows + 1;
	Mat result(width,height,CV_32FC1);

	matchTemplate(m_src, m_temple, result, match_method, Mat());
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	Point minLoc;
	Point maxLoc;
	Point templeLoc;
	double min, max;
	m_src.copyTo(m_dst);
	minMaxLoc(result, &min, &max,&minLoc,&maxLoc,Mat());//找到最大值最小值及其相应的位置
	if (match_method == CV_TM_SQDIFF||
		match_method == CV_TM_SQDIFF_NORMED)
	{
		templeLoc = minLoc;
	}
	else
	{
		templeLoc = maxLoc;
	}
	rectangle(m_dst,Rect(templeLoc.x,templeLoc.y,m_temple.cols,m_temple.rows), Scalar(0, 0, 255), 2, LINE_AA);
	rectangle(m_temple, Rect(templeLoc.x, templeLoc.y, m_temple.cols, m_temple.rows), Scalar(0, 0, 255), 2, LINE_AA);
	imshow(OUTPUT, m_dst);

}