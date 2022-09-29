//
//  main.cpp
//  hw1
//
//  Created by 이재하 on 2022/09/16.
//
// PSNR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

// #include <opencv/cv.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void bilinear_interpolation(Mat& image, Mat&img_out) {
    
    double rate = (double)img_out.rows / (double)image.rows;

    for (int i = 0; i < img_out.rows; i++) {
        for (int j = 0; j < img_out.cols; j++) {
            int p1_x = (int)(j / rate);
            int p1_y = (int)(i / rate);

            double a = (double)j / rate - (double)p1_x;
            double b = (double)i / rate - (double)p1_y;

            if (p1_x + 1 == image.cols && p1_y + 1 == image.cols) {
                uchar p1 = image.at<uchar>(p1_y, p1_x);

                img_out.at<uchar>(i, j) = p1;
            }
            else if (p1_x + 1 == image.cols) {
                uchar p1 = image.at<uchar>(p1_y, p1_x);
                uchar p2 = image.at<uchar>(p1_y + 1, p1_x);
                img_out.at<uchar>(i, j) = (1 - b) * p1 + b * p2;
            }
            else if (p1_y + 1 == image.cols) {
                uchar p1 = image.at<uchar>(p1_y, p1_x);
                uchar p2 = image.at<uchar>(p1_y, p1_x + 1);
                img_out.at<uchar>(i, j) = (1 - a) * p1 + a * p2;
            }
            else {
                double k1 = (1 - b) * (1 - a);
                double k2 = a * (1 - b);
                double k3 = (1 - a) * b;
                double k4 = a * b;

                uchar p1 = image.at<uchar>(p1_y, p1_x);
                uchar p2 = image.at<uchar>(p1_y, p1_x + 1);
                uchar p3 = image.at<uchar>(p1_y + 1, p1_x);
                uchar p4 = image.at<uchar>(p1_y + 1, p1_x + 1);

                img_out.at<uchar>(i, j) = k1 * p1 + k2 * p2 + k3 * p3 + p4 * k4;
            }
         }
    }
}

void rotation(Mat& image, Mat &img_out, double Deg)
{
    double rad = Deg * M_PI / 180;
    double c = cos(rad), s = sin(-rad);
    double center_x = (double)image.cols / 2;
    double center_y = (double)image.rows / 2;

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            int orig_x = (int)(center_x + ((double)y - center_y) * s + ((double)x - center_x) * c);
            int orig_y = (int)(center_y + ((double)y - center_y) * c - ((double)x - center_x) * s);

            if ((orig_y >= 0 && orig_y < image.rows) && (orig_x >= 0 && orig_x < image.cols)) {
                img_out.at<uchar>(y, x) = image.at<uchar>(orig_y, orig_x);
            }
            else {
                img_out.at<uchar>(y, x) = 0;
            }
        }
    }
}

int main()
{
    Mat img_in;
    Mat img_out;
    
    // image 읽고 gray로 바꾸기
    img_in = imread("/Users/ijaeha/Desktop/hw1/hw1/Lena_256x256.png");
    cvtColor(img_in, img_in, cv::COLOR_RGB2GRAY);
    imshow("source img", img_in);
    
    int action;
    cout << "원하는 동작? 확장(1)? or 회전(2)? : ";
    cin >> action;
    
    if (action==1) {
        int size;
        cout << "몇 픽셀? : ";
        cin >> size;
        
        img_out = Mat(size, size, img_in.type());

        bilinear_interpolation(img_in, img_out);
        imshow("output image", img_out);
        waitKey(0);
    }
    else if (action==2) {
        double deg;
        cout << "몇 도? : ";
        cin >> deg;
        
        img_out = Mat(img_in.rows, img_in.cols, img_in.type());

        rotation(img_in, img_out, deg);
        imshow("output image", img_out);
        waitKey(0);
    }

    return 0;
}
