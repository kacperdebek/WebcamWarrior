#include "WebcamControl.hpp"

void WebcamControl::run()
{
	VideoCapture vcap;
	Mat image;
	Mat image_gray;
	Mat result;
	Mat res;

	vector<vector<Point> >contours;
	vector<Vec4i>hierarchy;
	if (!vcap.open(0))
	{
		cout << "Error opening video stream or file" << endl;
		return;
	}
	while (true)
	{
		if (!vcap.read(image))
		{
			cout << "No frame" << endl;
			waitKey();
		}
		resize(image, image, Size(1280, 720));
		flip(image, image, 1);
		cvtColor(image, image_gray, COLOR_BGR2GRAY);

		threshold(image_gray, res, webcamThreshold, 255, THRESH_BINARY);
		int savedContour = -1;
		double maxArea = 0.0;
		findContours(res, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
		for (int i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area > maxArea)
			{
				maxArea = area;
				savedContour = i;
			}

		}
		if(maxArea < 50)
			savedContour = -1;
		Mat img(720, 1280, CV_8UC3, Scalar(0, 0, 0));
		cvtColor(img, img, COLOR_BGR2GRAY);
		drawContours(img, contours, savedContour, Scalar(255, 255, 255), FILLED, 8);
		Moments m2 = moments(img, true);
		x = m2.m10 / m2.m00;
		y = m2.m01 / m2.m00;
		Point p2(x, y);
		circle(img, p2, 5, Scalar(128, 0, 0), -1);

		imshow("Cam", img);
		if (waitKey(1) == 27)
			break;
	}
}
int WebcamControl::getX()
{
	return this->x;
}
int WebcamControl::getY()
{
	return this->y;
}
void WebcamControl::setThreshold(int targetThreshold)
{
	this->webcamThreshold = targetThreshold;
}
int WebcamControl::getThreshold()
{
	return this->webcamThreshold;
}