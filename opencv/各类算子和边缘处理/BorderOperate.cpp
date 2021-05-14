
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
	*ͼ���Եһ�߶�������ֵ��ԾǨ����Ե��������λ��ΪX�ᣬ����ֵΪY������ߣ�����һ�׵�
	*��һ�׵�������ĳ�̶ֳ���������Ե��������ֵ�仯Խ��Խ�п�����ͼ���Ե��Ҳ������������Ҫ��Ե
	*�Ƿֱ��ͼƬ�и��ֲ�ͬ��Ʒ����Ҫ����
	*/
	Mat dest;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);//��˹ģ����ƫ��
	cvtColor(src, src, CV_BGR2GRAY);//�Ҷȴ���
	imshow("Input", src);

	Mat xgrad, ygrad;
	Sobel(src, xgrad, CV_16S, 1, 0, 3);//Sobel��������δ��������Ļ����ṹ�͹�����ʲô
	Sobel(src, ygrad, CV_16S, 0, 1, 3);//Sobel��������δ��������Ļ����ṹ�͹�����ʲô

	convertScaleAbs(xgrad, xgrad);//ͼ����ǿ
	convertScaleAbs(ygrad, ygrad);

	addWeighted(xgrad, 0.5, ygrad, 0.5, 0, dest);
	imshow("Output", dest);

	waitKey(0);
#endif // TestUnit_Sobel

#ifdef TestUnit_Laplance
	/*
	*���Ե�����Ķ��׵�Ϊ�㴦������һ�׵������ֵ������ͼ��ı�Ե
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