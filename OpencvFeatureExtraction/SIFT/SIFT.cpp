#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

Mat img1, img2, src_gray, dst;

const char* INPUT = "Input";
const char* OUTPUT = "Output";

int main()
{
	img1 = imread("pic_JK.jpg");
	img2 = imread("pic_JK.jpg");
	if (img1.empty()|| img2.empty())
	{
		cout << "this photo could not load ..." << endl;
	}
	namedWindow(INPUT);
	namedWindow(OUTPUT);

	//-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
	detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

	//-- Step 2: Matching descriptor vectors with a brute force matcher
   // Since SURF is a floating-point descriptor NORM_L2 is used
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
	std::vector< DMatch > matches;
	matcher->match(descriptors1, descriptors2, matches);

	//-- Draw matches
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);

	//-- Show detected matches
	imshow("Matches", img_matches);
	waitKey();
	return 0;
}