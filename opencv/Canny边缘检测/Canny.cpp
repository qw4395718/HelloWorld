#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define UnitTest1

/*
*1.高斯模糊-GuassianBlur
*2.灰度转换-cvtcolor
*3.计算梯度-sobel/scharr
*4.非最大信号抑制
*5.高低阈值输出二值图像
*/

void Canny_Demo(int, void*);

Mat src,src_gray,dst;
int t1_value = 50;
int Max_value = 255;
char OUTPUT_TITLE[] = "Output";
int main()
{
	
	src = imread("pic_JK.jpg");
	if (!src.data)
	{
		cout << "img could not load ..." << endl;
		return -1;
	}
	imshow("InPut", src);
	cvtColor(src, src_gray, CV_RGB2GRAY);
	namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
	createTrackbar("threshold value:", OUTPUT_TITLE, &t1_value, Max_value, Canny_Demo);
	Canny_Demo(0, 0);

	waitKey(0);
	return 0;
}

void Canny_Demo(int, void*)
{
	Mat Dst,Mask;
	blur(src_gray, src_gray, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	Canny(src_gray, dst, t1_value, t1_value * 2, 3, false);
	Dst.create(src.size(), src.type());
	src.copyTo(Dst, dst);
	imshow(OUTPUT_TITLE, Dst);
}