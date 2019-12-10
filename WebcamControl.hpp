#pragma once
#include "GenericCHeader.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
class WebcamControl
{
private:
	int x;
	int y;
	int webcamThreshold;
public:
	void run();
	int getX();
	int getY();
	void setThreshold(int targetThreshold);
	int getThreshold();
};