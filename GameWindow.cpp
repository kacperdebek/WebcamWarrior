#include "WebcamControl.hpp"
#define SPAWN_DELAY 3
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Strzelnica");
    WebcamControl webcamThread;
    sf::Thread thread(&WebcamControl::run, &webcamThread);
    thread.launch();
    sf::CircleShape target;
    target.setRadius(30);
    target.setFillColor(sf::Color::Red);
    target.setOrigin(target.getRadius(), target.getRadius());
    sf::Clock deltaClock;
    sf::Time dt;
    int randX = rand() % 540 + 50;
    int randY = rand() % 360 + 50;
    target.setPosition(randX, randY);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (dt <= sf::seconds(SPAWN_DELAY))
        {

            window.clear();
            window.draw(target);
        }
        else
        {
            randX = rand() % 540 + 50;
            randY = rand() % 360 + 50;
            target.setPosition(randX, randY);
            dt = sf::seconds(0);
        }
        dt += deltaClock.restart();
        window.display();
    }
    return 0;
}