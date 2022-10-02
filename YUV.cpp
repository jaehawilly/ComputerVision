#include <math.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void RGBtoYUV(Mat& img_in, Mat& img_out) {
	for (int row = 0; row < img_in.rows; row++)
	{
		for (int col = 0; col < img_in.cols; col++)
		{
			uchar b = img_in.at<Vec3b>(row, col)[0];
			uchar g = img_in.at<Vec3b>(row, col)[1];
			uchar r = img_in.at<Vec3b>(row, col)[2];

			uchar y = (0.257 * r) + (0.504 * g) + (0.098 * b) + 16;
			uchar u = -(0.148 * r) - (0.291 * g) + (0.439 * b) + 128;
			uchar v = (0.439 * r) - (0.368 * g) - (0.071 * b) + 128;

			img_out.at<Vec3b>(row, col)[0] = y;
			img_out.at<Vec3b>(row, col)[1] = u;
			img_out.at<Vec3b>(row, col)[2] = v;
		}
	}
}
int main()
{
	Mat img_in = imread("Lena.png");
	imshow("source img", img_in);
	Mat img_out1 = Mat(img_in.cols, img_in.rows, img_in.type());
	RGBtoYUV(img_in, img_out1);
	imshow("img_out1", img_out1);

	Mat img_out2;
	cvtColor(img_in, img_out2, COLOR_BGR2YUV);
	imshow("img_out2", img_out2);
	for (int i = 0; i < 30; i++) {
		printf("%d번째 데이터: %d, %d\n", i, img_out1.data[i], img_out2.data[i]);
	}
	waitKey(0);
	return 0;
}
