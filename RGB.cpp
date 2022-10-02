#include <math.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat img_in;
	img_in = imread("Lena.png");
	imshow("source img", img_in);
	uchar* img_data = img_in.data;

	for (int i = 0; i < 15; i++) {
		uchar pixel = img_data[i];
		printf("%d번째 : %d\n", i, pixel);
	}
	waitKey(0);
	return 0;
}
