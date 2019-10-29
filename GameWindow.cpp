#include "WebcamControl.hpp"
#define SPAWN_DELAY 10
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Strzelnica");
    WebcamControl webcamThread;
    sf::Thread thread(&WebcamControl::run, &webcamThread);
    thread.launch();
    sf::CircleShape target;
    sf::CircleShape aim;
    target.setRadius(30);
    target.setFillColor(sf::Color::Blue);
    target.setOrigin(target.getRadius(), target.getRadius());
    aim.setRadius(10);
    aim.setFillColor(sf::Color::Red);
    aim.setOrigin(aim.getRadius(), aim.getRadius());
    sf::Clock deltaClock;
    sf::Time dt;
    bool spacePressed = false;
    bool targetShot = false;
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
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if ((abs(randX - webcamThread.getX()) < 30) && (abs(randY - webcamThread.getY()) < 30) && !spacePressed) {
                        spacePressed = true;
                        if (!targetShot) {
                            targetShot = true;
                            cout << "Bullseye!" << endl;
                            dt = sf::seconds(9.5);
                        }
                    }
                    else if (!spacePressed)
                    {
                        spacePressed = true;
                        cout << "Miss!" << endl;
                    }
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    spacePressed = false;
                }
            }
        }
        aim.setPosition(webcamThread.getX(), webcamThread.getY());
        if (dt <= sf::seconds(SPAWN_DELAY))
        {
            window.clear();
            window.draw(target);
            window.draw(aim);
        }
        else
        {
            targetShot = false;
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
