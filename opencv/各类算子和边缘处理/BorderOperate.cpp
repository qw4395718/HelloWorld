
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//#define TestUnit_Border
//#define TestUnit_Sobel
#define TestUnit_Laplance

int main()
{
	Mat src;
	src = imread("pic_JK.jpg");
	if (!src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}

	#ifdef TestUnit_Border
	
	int flag = 0;
	int border_type = BORDER_WRAP;
	Scalar color;
	int top = (int)(0.05*src.rows);
	int bottom = (int)(0.05*src.rows);
	int left = (int)(0.05*src.cols);
	int right = (int)(0.05*src.cols);

	while (true)
	{
		flag = waitKey(500);
		if ((char)flag == 27)
		{
			break;
		}
		if ((char)flag == 'c')
		{
			border_type = BORDER_CONSTANT;
		}
		if ((char)flag == 'r')
		{
			border_type = BORDER_REPLICATE;
		}
		color = Scalar(255, 0, 0, 1);
		copyMakeBorder(src, src, top, bottom, left, right, border_type, color);
		imshow("Output", src);
	}
	#endif // TestUnit_Border
	
#ifdef TestUnit_Sobel
	/*
	*图像边缘一边都有像素值的跃迁，边缘函数（以位置为X轴，像素值为Y轴的曲线）求其一阶导
	*其一阶导可以在某种程度上象征边缘，当像素值变化越大，越有可能是图像边缘，也是其轮廓的重要边缘
	*是分辨出图片中各种不同物品的重要特征
	*/
	Mat dest;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);//高斯模糊无偏差
	cvtColor(src, src, CV_BGR2GRAY);//灰度处理
	imshow("Input", src);

	Mat xgrad, ygrad;
	Sobel(src, xgrad, CV_16S, 1, 0, 3);//Sobel算子是如何创建，它的基本结构和功能是什么
	Sobel(src, ygrad, CV_16S, 0, 1, 3);//Sobel算子是如何创建，它的基本结构和功能是什么

	convertScaleAbs(xgrad, xgrad);//图像增强
	convertScaleAbs(ygrad, ygrad);

	addWeighted(xgrad, 0.5, ygrad, 0.5, 0, dest);
	imshow("Output", dest);

	waitKey(0);
#endif // TestUnit_Sobel

#ifdef TestUnit_Laplance
	/*
	*其边缘函数的二阶导为零处，代表一阶导的最大值，代表图像的边缘
	*/
	Mat dest;
	GaussianBlur(src,src,Size(3,3),0);
	cvtColor(src, src, CV_BGR2GRAY);
	//Laplacian
	Laplacian(src, dest, CV_16S, 3);
	convertScaleAbs(dest, dest);
	imshow("Output", dest);
	waitKey(0);
#endif // TestUnit_Laplance

	return 0;
}