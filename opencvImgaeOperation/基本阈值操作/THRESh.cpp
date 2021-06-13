#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv.hpp>
using namespace cv;
using namespace std;

#define UnitTest1
	Mat src;
#ifdef UnitTest1
	int threshold_value = 127;
	int threshold_maxValue = 255;
	Mat src_gray, dst;
	void threshold_Demo(int, void*);
	const char* output_title = "Output img";
#endif // UnitTest1


int main()
{

	src = imread("pic.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	imshow("Input",src);

#ifdef UnitTest1


	namedWindow(output_title, CV_WINDOW_AUTOSIZE);

	createTrackbar("Threshold Value", output_title, &threshold_value, threshold_maxValue, threshold_Demo);
	threshold_Demo(0, 0);

#endif // 


	waitKey(0);
	return 0;
}

void threshold_Demo(int, void*)
{
	cvtColor(src, src_gray, CV_RGB2GRAY);
	threshold(src_gray, dst, threshold_value, threshold_maxValue, THRESH_BINARY);//二值化处理
	imshow("Output img", dst);

}