#include "WebcamControl.hpp"
void WebcamControl::run()
{
    VideoCapture vcap;
    Mat image;
    Mat image_gray;
    Mat result;
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
        threshold(image_gray, result, 200, 255, THRESH_BINARY);
        Moments m = moments(result, true);
        x = m.m10 / m.m00;
        y = m.m01 / m.m00;
        Point p(x, y);
        circle(result, p, 5, Scalar(128, 0, 0), -1);
		
        imshow("Cam", result);
        if (waitKey(1) == 27)
            break;
    }
}
int WebcamControl::getX()
{
    return x;
}
int WebcamControl::getY()
{
    return y;
}