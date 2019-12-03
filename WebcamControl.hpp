#pragma once
#include "SFMLHeader.hpp"
#include "GenericCHeader.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
class WebcamControl
{
public:
    int x;
    int y;
	int webcamThreshold;
    void run();
    int getX();
    int getY();
	void setThreshold(int targetThreshold);
	int getThreshold();
};