#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//直方图绘制

Mat m_src, m_singleSrc, m_dst;
char INPUT[] = "Input";
char OUTPUT[] = "Output";

int main()
{
	m_src = imread("pic_JK.jpg");
	if (!m_src.data)
	{
		cout << "could not load img..." << endl;
		return -1;
	}
	namedWindow(INPUT, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT, CV_WINDOW_AUTOSIZE);
	imshow(INPUT, m_src);


	vector<Mat> bgr_planes;
	split(m_src, bgr_planes);
	//imshow(OUTPUT, bgr_planes[2]);//检测结果

	//计算直方图
	int iHighSize = 256;
	float fRange[] = { 0,255 };
	const float *pHighRanges = { fRange };
	Mat m_blueHist, m_greenHist, m_redHist;
	calcHist(&bgr_planes[0], 1, 0,Mat(), m_blueHist,1, &iHighSize, &pHighRanges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), m_greenHist, 1, &iHighSize, &pHighRanges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), m_redHist, 1, &iHighSize, &pHighRanges, true, false);

	//归一化处理
	int iHistHigh = 400;
	int iHistWidth = 512;
	int iBinWidth = iHistWidth / iHighSize;
	Mat HistImage(iHistWidth, iHistHigh, CV_8UC3, Scalar(0, 0, 0));
	normalize(m_blueHist, m_blueHist, 0, iHistHigh, NORM_MINMAX, -1, Mat());
	normalize(m_greenHist, m_greenHist, 0, iHistHigh, NORM_MINMAX, -1, Mat());
	normalize(m_redHist, m_redHist, 0, iHistHigh, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < iHighSize; i++)
	{
		line(HistImage, Point((i - 1)*iBinWidth, iHistHigh - cvRound(m_blueHist.at<float>(i - 1))),
			Point((i)*iBinWidth, iHistHigh - cvRound(m_blueHist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);

		line(HistImage, Point((i - 1)*iBinWidth, iHistHigh - cvRound(m_greenHist.at<float>(i - 1))),
			Point((i)*iBinWidth, iHistHigh - cvRound(m_greenHist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);

		line(HistImage, Point((i - 1)*iBinWidth, iHistHigh - cvRound(m_redHist.at<float>(i - 1))),
			Point((i)*iBinWidth, iHistHigh - cvRound(m_redHist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow(OUTPUT, HistImage);


	waitKey(0);
	return 0;
}