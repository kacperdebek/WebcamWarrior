#include "WebcamControl.hpp"
#include "SpawnTrack.h"

#define SPAWN_DELAY 10

#include <iostream>
#include "Menu.hpp"
#define SPAWN_DELAY 3

void displayBackgroundAndUI(sf::RenderWindow &window,
	sf::Sprite& backgroundSprite,
	sf::Text& pointTotal,
	sf::CircleShape& target,
	int points) {
	window.clear();
	pointTotal.setString("Points: " + to_string(points));
	window.draw(backgroundSprite);
	window.draw(pointTotal);
	window.draw(target);
}

void displayGameObjects(sf::RenderWindow& window, SpawnTrack (&spawnTracks)[5]) {
	for (int i = 0; i < 5; i++) {
		spawnTracks[i].update();
		spawnTracks[i].draw(window);
	}
}

void initializeText(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color)
{
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(textSize);
	text.setFillColor(color);
	text.setPosition(yPosition, xPosition);
}
void initializeCircle(sf::CircleShape& circle, int radius, const sf::Color& color)
{
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
}
int main()
{
	srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Strzelnica");
    WebcamControl webcamThread;
    sf::Thread thread(&WebcamControl::run, &webcamThread);
    thread.launch();

    sf::Text pointTotal;
    sf::Text gunpointNotFound;
    sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	// Game logic setup
	SpawnTrack spawnTracks[5];
	int positioner = 592;
	for (int i = 0; i < 5; i++) {
		spawnTracks[i] = SpawnTrack(positioner,
			rand() % 3 + 1,
			rand() % 250);
		positioner -= 128;
	}

    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Couldn't load the font" << endl;
        return -1;
    }
	if (!backgroundTexture.loadFromFile("background.jpg")) {
		cout << "Couldn't load the background image" << endl;
		return -1;
	}

	backgroundSprite.setTexture(backgroundTexture);

    int points = 0;
	initializeText(pointTotal, font, 18, 460, 5, "Points: " + to_string(points), sf::Color::White);
	initializeText(gunpointNotFound, font, 26, 210, 130, "CANNOT LOCATE CONTROLLER", sf::Color::Yellow);
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Pop.wav")){
        cout << "Couldn't load the sound file" << endl;
        return -1;
    }
    sf::Sound popSound;
    popSound.setBuffer(buffer);
    sf::CircleShape target;
    sf::CircleShape aim;
	initializeCircle(target, 30, sf::Color::Red);
	initializeCircle(aim, 10, sf::Color::Blue);
    target.setOutlineColor(sf::Color::Red);
    target.setOutlineThickness(5);
    
    sf::Time dt;
    bool spacePressed = false;
    bool targetShot = false;
	bool playPressed = false;
    int randX = rand() % 540 + 50;
    int randY = rand() % 360 + 50;
    target.setPosition(randX, randY);
	Menu menu(640, 480);
	sf::Clock deltaClock;
	static std::once_flag onceFlag;
    while (window.isOpen())
    {
		
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && playPressed) {
                    if ((abs(randX - webcamThread.getX()) < 30) && (abs(randY - webcamThread.getY()) < 30) && !spacePressed) {
                        spacePressed = true;
                        if (!targetShot) {
                            targetShot = true;
                            popSound.play();
                            cout << "Bullseye!" << endl;
                            points += 10;
                            target.setOutlineColor(sf::Color::Green);
                            dt = sf::seconds(9.5);
                        }
                    }
                    else if (!spacePressed && playPressed)
                    {
                        spacePressed = true;
                        cout << "Miss!" << endl;
                        points -= 1;
                    }
                }
				else if (event.key.code == sf::Keyboard::Escape && playPressed)
				{
					playPressed = false;
				}
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space && playPressed) {
                    spacePressed = false;
                }
				else if (event.key.code == sf::Keyboard::Up)
					menu.MoveUp();
				else if (event.key.code == sf::Keyboard::Down)
					menu.MoveDown();
				else if (event.key.code == sf::Keyboard::Enter && !playPressed)
				{
					switch (menu.GetPressedItem())
					{
						case 0:
							std::cout << "Play button has been pressed" << std::endl;
							playPressed = true;
							break;
						case 1:
							std::cout << "Option button has been pressed" << std::endl;
							break;
						case 2:
							thread.terminate();
							window.close();
							break;
					}
				}
            }
        }
        aim.setPosition(webcamThread.getX(), webcamThread.getY());
        if (dt <= sf::seconds(SPAWN_DELAY))
        {
			displayBackgroundAndUI(window, backgroundSprite, pointTotal, target, points);
			displayGameObjects(window, spawnTracks);

            if (webcamThread.getX() < 0 || webcamThread.getY() < 0) {
                window.draw(gunpointNotFound);
            }
            else {
                window.draw(aim);
            }
        }
        else
        {
            targetShot = false;
            target.setOutlineColor(sf::Color::Red);
            randX = rand() % 540 + 50;
            randY = rand() % 360 + 50;
            target.setPosition(randX, randY);
            dt = sf::seconds(0);
        }

		if (playPressed)
		{
			std::call_once(onceFlag, [&] {deltaClock.restart();});
			
			aim.setPosition(webcamThread.getX(), webcamThread.getY());
			if (dt <= sf::seconds(SPAWN_DELAY))
			{
				displayBackgroundAndUI(window, backgroundSprite, pointTotal, target, points);
				displayGameObjects(window, spawnTracks);

				if (webcamThread.getX() < 0 || webcamThread.getY() < 0) {
					window.draw(gunpointNotFound);
				}
				else {
					window.draw(aim);
				}
			}
			else
			{
				targetShot = false;
				target.setOutlineColor(sf::Color::Red);
				randX = rand() % 540 + 50;
				randY = rand() % 360 + 50;
				target.setPosition(randX, randY);
				dt = sf::seconds(0);
			}

			dt += deltaClock.restart();

		}
		else
		{
			window.clear();
			menu.draw(window);
		}

        window.display();
    }
    return 0;
}