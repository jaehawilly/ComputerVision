#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat CreateZeroPadding_gray(Mat& img_in, int n) {
    Mat zeroPadding = Mat(img_in.cols + n, img_in.rows + n, img_in.type());

    for (int row = 0; row < zeroPadding.rows; row++) {
        for (int col = 0; col < zeroPadding.cols; col++) {
            if ((row >= n && row < zeroPadding.rows - n) && (col >= n && col < zeroPadding.cols - n)) {
                zeroPadding.at<uchar>(row, col) = img_in.at<uchar>(row - n, col - n);
            }
            else {
                zeroPadding.at<uchar>(row, col) = 0;
            }
        }
    }

    return zeroPadding;
}

Mat CreateZeroPadding_rgb(Mat& img_in, int n) {
    Mat zeroPadding = Mat(img_in.cols + n, img_in.rows + n, img_in.type());

    for (int row = 0; row < zeroPadding.rows; row++) {
        for (int col = 0; col < zeroPadding.cols; col++) {
            if ((row >= n && row < zeroPadding.rows - n) && (col >= n && col < zeroPadding.cols - n)) {
                zeroPadding.at<Vec3b>(row, col)[0] = img_in.at<Vec3b>(row - n, col - n)[0];
                zeroPadding.at<Vec3b>(row, col)[1] = img_in.at<Vec3b>(row - n, col - n)[1];
                zeroPadding.at<Vec3b>(row, col)[2] = img_in.at<Vec3b>(row - n, col - n)[2];
            }
            else {
                zeroPadding.at<Vec3b>(row, col)[0] = 0;
                zeroPadding.at<Vec3b>(row, col)[1] = 0;
                zeroPadding.at<Vec3b>(row, col)[2] = 0;
            }
        }
    }

    return zeroPadding;
}

void filtering_gray(Mat& img_in, Mat& img_out, double* kernal_array, int n) {
    int size = 2 * n + 1;

    //zero padding ª˝º∫
    Mat paddingImg = CreateZeroPadding_gray(img_in, n);
    
    for (int row = n; row < paddingImg.rows - n; row++)
    {
        for (int col = n; col < paddingImg.cols - n; col++)
        {
            double p = 0.0;
            
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    p += paddingImg.at<uchar>(row + (i - n), col + (i - n)) * kernal_array[i * size + j];
                }
            }

            img_out.at<uchar>(row - n, col - n) = p;
        }
    }
}

void filtering_rgb(Mat& img_in, Mat& img_out, double* kernal_array, int n) {
    int size = 2 * n + 1;

    //zero padding ª˝º∫
    Mat paddingImg = CreateZeroPadding_rgb(img_in, n);

    for (int row = n; row < paddingImg.rows - n; row++)
    {
        for (int col = n; col < paddingImg.cols - n; col++)
        {
            float r = 0.0;
            float g = 0.0;
            float b = 0.0;

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    b += paddingImg.at<Vec3b>(row + (i - n), col + (i - n))[0] * kernal_array[i * size + j];
                    g += paddingImg.at<Vec3b>(row + (i - n), col + (i - n))[1] * kernal_array[i * size + j];
                    r += paddingImg.at<Vec3b>(row + (i - n), col + (i - n))[2] * kernal_array[i * size + j];
                }
            }

            img_out.at<Vec3b>(row - n, col - n)[0] = b;
            img_out.at<Vec3b>(row - n, col - n)[1] = g;
            img_out.at<Vec3b>(row - n, col - n)[2] = r;
        }
    }
}

int main()
{
    Mat img_in = imread("/Users/ijaeha/Desktop/test/test/test/Lena.png");
    imshow("source img", img_in);
    
    double moving_average[] = { 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                        1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                        1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0 };
    
    double Laplacian[] = { 0, 1, 0,
                        1, -4, 1,
                        0, 1, 0 };

    double sharpening[] = { 0, 1, 0,
                        1, -3, 1,
                        0, 1, 0 };

    Mat img_moving_average = Mat(img_in.cols, img_in.rows, img_in.type());
    Mat img_Laplacian = Mat(img_in.cols, img_in.rows, img_in.type());
    Mat img_sharpening = Mat(img_in.cols, img_in.rows, img_in.type());
    
    filtering_rgb(img_in, img_moving_average, moving_average, 1);
    filtering_rgb(img_in, img_Laplacian, Laplacian, 1);
    filtering_rgb(img_in, img_sharpening, sharpening, 1);

    imshow("Blurring image", img_moving_average);
    imshow("Laplacian image", img_Laplacian);
    imshow("Sharpening image", img_sharpening);

    waitKey(0);

    return 0;
}
