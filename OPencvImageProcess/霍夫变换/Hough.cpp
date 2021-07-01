#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//#define UnitTest1
#define UnitTest2
//#define Whitegroud

Mat src, src_black,src_gray, dst;



int main()
{
	src = imread("circle.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	char INPUT[] = "Input";
	char OUTPUT[] = "Output";
	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);

#ifdef Whitegroud
	
	for (size_t i = 0; i < src.rows; i++)
	{
		for (size_t j = 0;j < src.cols; j++)
		{
			if (src.channels() == 3)
			{
				src.at<Vec3b>(i, j)[0] = 255 - src.at<Vec3b>(i, j)[0];
				src.at<Vec3b>(i, j)[1] = 255 - src.at<Vec3b>(i, j)[1];
				src.at<Vec3b>(i, j)[2] = 255 - src.at<Vec3b>(i, j)[2];
			}
			else if (src.channels() == 1)
			{
				src.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);
			}
		}
	}
#endif // White
	//extract edge
	//imshow(INPUT, src);

#ifdef UnitTest1
	Canny(src, src_gray, 100, 200);//最后两个数是阈值（里面由模糊处理）
	cvtColor(src_gray, dst, CV_GRAY2BGR);
	vector<Vec4f> plines;
	HoughLinesP(src_gray, plines, 1, CV_PI / 180.0, 10, 0, 20);//
	Scalar color = Scalar(0, 255, 0);
	for (size_t i = 0; i < plines.size(); i++)
	{
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);
	}
	imshow(OUTPUT, dst);

#endif // 

#ifdef UnitTest2
	//均值滤波
	medianBlur(src, src_black, 3);
	cvtColor(src_black, src_black, CV_BGR2GRAY);

	//霍夫圆检测
	vector<Vec3f> pcircles;
	HoughCircles(src_black, pcircles, CV_HOUGH_GRADIENT, 1, 10,100,30,5,50);
	src.copyTo(dst);

	for (size_t i = 0; i < pcircles.size(); i++)
	{
		Vec3f cc = pcircles[i];
		circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 31, 0), 2, LINE_AA);
		circle(dst, Point(cc[0], cc[1]),2, Scalar(0, 31, 31), 2, LINE_AA);
	}

	imshow(OUTPUT, dst);
#endif // UnitTest2



	waitKey(0);
	return 0;
}
