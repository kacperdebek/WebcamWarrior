#include "WebcamControl.hpp"
#include "SpawnTrack.h"
#include "Monster.h"
#include <iostream>
#include "Menu.hpp"
#define SPAWN_DELAY 10
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280


void displayBackgroundAndUI(sf::RenderWindow &window,
	sf::Sprite& backgroundSprite,
	sf::Text& pointTotal,
	int points) {
	window.clear();
	pointTotal.setString("Points: " + to_string(points));
	window.draw(backgroundSprite);
	window.draw(pointTotal);
}

void displayGameObjects(sf::RenderWindow& window, SpawnTrack (&spawnTracks)[5]) {
	for (int i = 0; i < 5; i++) {
		spawnTracks[i].update();
		spawnTracks[i].draw(window);
	}
}

bool checkForCollisions(SpawnTrack tracks[5], WebcamControl& webcamThread) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (tracks[i].sockets[j].checkCollision(webcamThread.getX(), webcamThread.getY(), 30)) {
				cout << "Collision! " << tracks[i].sockets[j].checkCollision(webcamThread.getX(), webcamThread.getY(), 30);
				tracks[i].sockets[j].unmount();
				return true;
			}
		}
	}
	return false;
}

void updateEntities(Monster monsters[5], SpawnTrack tracks[5]) {
	for (int i = 0; i < 5; i++) {
		if (!monsters[i].checkMount() && monsters[i].hasCooldown() > 0) {
			cout << "Entered the loop: mounter | cd " << monsters[i].checkMount() << " " << monsters[i].hasCooldown() << "\n";
			while (true) {
				cout << "Checking sockets...";
				SpawnSocket& helper = tracks[rand() % 4].sockets[rand() % 9];
				if (!helper.checkMount() && helper.isOutOfWindow()) {
					helper.mount(monsters[i]);
					cout << "Mount\n";
					
					break;
				}
			}
		}
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
int main()
{
	srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Strzelnica");
	window.setFramerateLimit(30);
	
    WebcamControl webcamThread;
    sf::Thread thread(&WebcamControl::run, &webcamThread);
    thread.launch();

    sf::Text pointTotal;
    sf::Text gunpointNotFound;
    sf::Font font;

	sf::Texture backgroundTexture;
	sf::Texture aimTexture;
	sf::Texture monsterTexture;
	sf::Sprite backgroundSprite;
	sf::Sprite aimSprite;
	sf::Sprite monsterSprite;

	// Game logic setup
	SpawnTrack spawnTracks[5];
	int positioner = 592;
	for (int i = 0; i < 5; i++) {
		spawnTracks[i] = SpawnTrack(positioner,
			rand() % 2 + 1,
			rand() % 250);
		positioner -= 128;
	}

	// Graphics setup
    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Couldn't load the font" << endl;
        return -1;
    }
	if (!backgroundTexture.loadFromFile("background.jpg")) {
		cout << "Couldn't load the background image" << endl;
		return -1;
	}
	if (!aimTexture.loadFromFile("aim.png")) {
		cout << "Couldn't load the aim texture" << endl;
		return -1;
	}
	if (!monsterTexture.loadFromFile("testmonster.png")) {
		cout << "Couldn't load the monster texture" << endl;
		return -1;
	}

	backgroundSprite.setTexture(backgroundTexture);
	aimSprite.setTexture(aimTexture);
	monsterSprite.setTexture(monsterTexture);

	// Game objects setup
	Monster monsters[5];
	for (int i = 0; i < 5; i++) {
		monsters[i] = Monster(1, 10, 60, monsterSprite);
		while (true) {
			SpawnSocket& helper = spawnTracks[rand() % 4].sockets[rand() % 9];
			if (!helper.checkMount() && helper.isOutOfWindow()) {
				cout << "Monster mounted!\n";
				helper.mount(monsters[i]);
				break;
			}
		}
	}

    int points = 0;
	initializeText(pointTotal, font, 18, WINDOW_HEIGHT - 30, 5, "Points: " + to_string(points), sf::Color::White);
	initializeText(gunpointNotFound, font, 26, (WINDOW_HEIGHT / 2), (WINDOW_WIDTH / 3), "CANNOT LOCATE CONTROLLER", sf::Color::Yellow);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Pop.wav")){
        cout << "Couldn't load the sound file" << endl;
        return -1;
    }
    sf::Sound popSound;
    popSound.setBuffer(buffer);
    
    sf::Time dt;
    bool spacePressed = false;
	bool playPressed = false;

	Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);

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
                    if (checkForCollisions(spawnTracks, webcamThread) && !spacePressed) {
                        spacePressed = true;
                        popSound.play();
                        cout << "Bullseye!" << endl;
                        points += 10;
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
		if (playPressed)
		{
			aimSprite.setPosition(webcamThread.getX(), webcamThread.getY());

			updateEntities(monsters, spawnTracks);
			displayBackgroundAndUI(window, backgroundSprite, pointTotal, points);
			displayGameObjects(window, spawnTracks);

			if (webcamThread.getX() < 0 || webcamThread.getY() < 0) {
				window.draw(gunpointNotFound);
			}
			else {
				window.draw(aimSprite);
			}
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