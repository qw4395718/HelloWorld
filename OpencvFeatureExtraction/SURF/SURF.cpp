#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

Mat src, src_gray, dst;

const char* INPUT = "Input";
const char* OUTPUT = "Output";

int main()
{
	src = imread("pic_JK.jpg");
	if (src.empty())
	{
		cout << "this photo could not load ..." << endl;
	}
	namedWindow(INPUT);
	namedWindow(OUTPUT);
	
	//Step1:Detect the keypoints using SURF Detector
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints;
	detector->detect(src, keypoints);

	//Step2:Draw keypoints
	Mat img_keypoints;
	drawKeypoints(src, keypoints, img_keypoints);

	//Step3:Show detector keypoints

	imshow(OUTPUT, img_keypoints);
	
	waitKey(0);
	return 0;
}