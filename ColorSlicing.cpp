#include <math.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("myimage.jfif");
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			uchar b = src.at<Vec3b>(row, col)[0];
			uchar g = src.at<Vec3b>(row, col)[1];
			uchar r = src.at<Vec3b>(row, col)[2];
			//¾ó±¼»öÀÌ ¾Æ´Ò¶§
			if (120 > b || b > 200 || 150 > g || g > 255 || 170 > r || r > 255) {
				src.at<Vec3b>(row, col)[0] = 0;
				src.at<Vec3b>(row, col)[1] = 0;
				src.at<Vec3b>(row, col)[2] = 0;
			}
			//¾ó±¼»öÀÏ¶§
			else {
				src.at<Vec3b>(row, col)[0] = 255;
				src.at<Vec3b>(row, col)[1] = 255;
				src.at<Vec3b>(row, col)[2] = 255;
			}
		}
	}
	imshow("src", src);
	waitKey(0);
	return 0;
}