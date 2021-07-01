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
	imshow(INPUT, src);

	map_x.create(src.size(), CV_32FC1);//32bitµ¥Í¨µÀÍ¼Ïñ
	map_y.create(src.size(), CV_32FC1);
	updata_map();
	remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 50));
	imshow(OUTPUT, dst);
	waitKey(0);
	return 0;
}


void updata_map()
{
	for (size_t row = 0; row < src.rows; row++)
	{
		for (size_t col = 0; col < src.cols; col++)
		{
			switch (index)
			{
			case 0:
				if (col >= src.cols*0.25&&col <= src.cols*0.75&&
					row >= src.rows*0.25&&row <= src.rows*0.75)
				{
					map_x.at<float>(row, col) = 2 * (col - (src.cols*0.25));
					map_y.at<float>(row, col) = 2 * (row - (src.rows*0.25));
				}
				else
				{
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
			default:
				break;
			}
		}
	}
}