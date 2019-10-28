#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
/*int main()
{
    VideoCapture vcap;
    Mat image;
    Mat image_gray;
    Mat result;
    if (!vcap.open(0)) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    while (true)
    {
        if (!vcap.read(image)) {
            cout << "No frame" << endl;
            waitKey();
        }
        flip(image, image, 1);
        cvtColor(image, image_gray, COLOR_BGR2GRAY);
        threshold(image_gray, result, 150, 255, THRESH_BINARY);
        Moments m = moments(result, true);
        Point p(m.m10 / m.m00, m.m01 / m.m00);
        circle(result, p, 5, Scalar(128, 0, 0), -1);
        imshow("Cam", result);
        if (waitKey(1) >= 0) break;
    }
}*/