#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture vcap;
	Mat image;

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
		
		imshow("Cam", image);
		if (waitKey(1) >= 0) break;
	}
}