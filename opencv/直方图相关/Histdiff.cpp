#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

#define UnitTest1 CV_COMP_CORREL
#define UnitTest2 CV_COMP_CHISQR
#define UnitTest3 CV_COMP_INTERSECT
#define UnitTest4 CV_COMP_BHATTACHARYYA

//直方图比较

Mat m_test1, m_test2, m_base;

char BASE[] = "base";
char TEST1[] = "test1";
char TEST2[] = "test2";
char OUTPUT[] = "Output";

string convertToString(double d);
int main()
{
	m_base = imread("pic_JK.jpg");
	m_test1 = imread("pic_JK.jpg");
	m_test2 = imread("pic.jpg");
	if (!m_test1.data||!m_test2.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	
	//色彩空间转换
	cvtColor(m_base, m_base, CV_BGR2HSV);
	cvtColor(m_test1, m_test1, CV_BGR2HSV);
	cvtColor(m_test2, m_test2, CV_BGR2HSV);

	//直方图设置
	int iBinH = 50;
	int iBinS = 60;
	int iHistSize[] = { iBinH,iBinS };
	float H_Range[] = { 0,180 };//色彩
	float S_Range[] = { 0,256 };//饱和度
	const float *pRange[] = { H_Range,S_Range };
	int channels[] = { 0,1 };
	MatND HistBase;//多维Mat
	MatND HistTest1;
	MatND HistTest2;

	calcHist(&m_base, 1, channels, Mat(), HistBase, 2, iHistSize, pRange, true, false);
	normalize(HistBase, HistBase, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&m_test1, 1, channels, Mat(), HistTest1, 2, iHistSize, pRange, true, false);
	normalize(HistTest1, HistTest1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&m_test2, 1, channels, Mat(), HistTest2, 2, iHistSize, pRange, true, false);
	normalize(HistTest2, HistTest2, 0, 1, NORM_MINMAX, -1, Mat());

	double basebase = compareHist(HistBase, HistBase, UnitTest1);
	double basetest1 = compareHist(HistBase, HistTest1, UnitTest1);
	double basetest2 = compareHist(HistBase, HistTest2, UnitTest1);
	double test1test2 = compareHist(HistTest1, HistTest2, UnitTest1);

	putText(m_base, convertToString(basebase), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
	putText(m_test1, convertToString(basetest1), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
	putText(m_test2, convertToString(basetest2), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));

	namedWindow(BASE, CV_WINDOW_AUTOSIZE);
	namedWindow(TEST1, CV_WINDOW_AUTOSIZE);
	namedWindow(TEST2, CV_WINDOW_AUTOSIZE);

	imshow(BASE, m_base);
	imshow(TEST1, m_test1);
	imshow(TEST2, m_test2);

	waitKey(0);
	return 0;
}

string convertToString(double d)
{
	ostringstream os;
	if (os << d)
		return os.str();
	return "invalid conversion";
}