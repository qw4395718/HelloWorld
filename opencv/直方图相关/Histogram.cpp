#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int index = 0;
Mat src, map_x, map_y, dst;

void updata_map();

int main()
{
	src = imread("pic_JK.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	char INPUT[] = "Input";
	char OUTPUT[] = "Output";
	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);

	
	cvtColor(src, dst, CV_RGB2GRAY);
	imshow(INPUT, dst);
	equalizeHist(dst, dst);
	imshow(OUTPUT, dst);
	waitKey(0);
	return 0;
}