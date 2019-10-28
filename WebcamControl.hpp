#include <SFML/Window.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class WebcamControl
{
public:
    int x;
    int y;
    void run();
    int getX();
    int getY();
};