#include "WebcamControl.hpp"
#include "SpawnTrack.h"
#include "Monster.h"
#include <iostream>
#include "Menu.hpp"
#define SPAWN_DELAY 10
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define MONSTER_COUNT 5
#define SUPERMONSTER_COUNT 2

void displayBackgroundAndUI(sf::RenderWindow &window,
	sf::Sprite& backgroundSprite,
	sf::Text& pointTotal,
	sf::Text& healthDisplay,
	int points,
	int health) {
	window.clear();
	pointTotal.setString("POINTS: " + to_string(points));
	healthDisplay.setString("HEALTH: " + to_string(health));
	window.draw(backgroundSprite);
	window.draw(pointTotal);
	window.draw(healthDisplay);
}

void displayGameObjects(sf::RenderWindow& window, SpawnTrack (&spawnTracks)[SPAWN_TRACK_COUNT], int& health) {
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		spawnTracks[i].update(health);
		spawnTracks[i].draw(window);
	}
}

bool checkForCollisions(SpawnTrack tracks[SPAWN_TRACK_COUNT], WebcamControl& webcamThread, int& points, int& health) {
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		for (int j = 0; j < SPAWN_SOCKETS_PER_TRACK; j++) {
			if (tracks[i].sockets[j].checkCollision(webcamThread.getX(), webcamThread.getY(), 30)) {
				int* shotEffect = tracks[i].sockets[j].registerShot();
				health -= shotEffect[0];
				points += shotEffect[1];
				return true;
			}
		}
	}
	return false;
}

void updateEntities(Monster monsters[MONSTER_COUNT], Monster supermonsters[SUPERMONSTER_COUNT], SpawnTrack tracks[SPAWN_TRACK_COUNT]) {
	for (int i = 0; i < MONSTER_COUNT; i++) {
		if (!monsters[i].checkMount() || monsters[i].hasCooldown() > 0) {
			int memoryLimiter = 0;
			while (true && memoryLimiter < 4) {
				memoryLimiter++;
				SpawnSocket& helper = tracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
				if (!helper.checkMount() && helper.isOutOfWindow()) {
					helper.mount(monsters[i]);
					
					break;
				}
			}
		}
	}

	for (int i = 0; i < SUPERMONSTER_COUNT; i++) {
		if (!supermonsters[i].checkMount() || supermonsters[i].hasCooldown() > 0) {
			int memoryLimiter = 0;
			while (true && memoryLimiter < 4) {
				memoryLimiter++;
				SpawnSocket& helper = tracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
				if (!helper.checkMount() && helper.isOutOfWindow()) {
					helper.mount(supermonsters[i]);

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
	window.setFramerateLimit(60);
	
    WebcamControl webcamThread;
    sf::Thread thread(&WebcamControl::run, &webcamThread);
    thread.launch();

    sf::Text pointTotal;
	sf::Text healthDisplay;
    sf::Text gunpointNotFound;
    sf::Font font;

	sf::Texture backgroundTexture;
	sf::Texture aimTexture;
	sf::Texture monsterTexture;
	sf::Texture supermonsterTexture;

	sf::Sprite backgroundSprite;
	sf::Sprite aimSprite;
	sf::Sprite monsterSprite;
	sf::Sprite supermonsterSprite;

	// Game logic setup
	int playerHealth = 100;
	int points = 0;

	SpawnTrack spawnTracks[SPAWN_TRACK_COUNT];
	int positioner = 592;
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
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
	if (!supermonsterTexture.loadFromFile("supermonster.png")) {
		cout << "Couldn't load the super monster texture" << endl;
		return -1;
	}

	backgroundSprite.setTexture(backgroundTexture);
	aimSprite.setTexture(aimTexture);
	monsterSprite.setTexture(monsterTexture);
	supermonsterSprite.setTexture(supermonsterTexture);

	// Game objects setup
	Monster monsters[MONSTER_COUNT];
	for (int i = 0; i < MONSTER_COUNT; i++) {
		monsters[i] = Monster(
			1, // health points
			10, // points per kill
			10, // damage dealt to player
			60, // hitbox radius
			monsterSprite
		);
		while (true) {
			SpawnSocket& helper = spawnTracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
			if (!helper.checkMount() && helper.isOutOfWindow()) {
				cout << "Monster mounted!\n";
				helper.mount(monsters[i]);
				break;
			}
		}
	}

	Monster supermonsters[SUPERMONSTER_COUNT];
	for (int i = 0; i < SUPERMONSTER_COUNT; i++) {
		for (int i = 0; i < SUPERMONSTER_COUNT; i++) {
			supermonsters[i] = Monster(
				2, // health points
				20, // points per kill
				15, // damage dealt to player
				60, // hitbox radius
				supermonsterSprite
			);
			supermonsters[i].setCooldown(500);
		}
	}

	initializeText(healthDisplay, font, 18, 10, WINDOW_WIDTH - 200, "HEALTH: " + to_string(playerHealth), sf::Color::White);
	initializeText(pointTotal, font, 18, 10, 5, "SCORE: " + to_string(points), sf::Color::White);
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
                    if (checkForCollisions(spawnTracks, webcamThread, points, playerHealth) && !spacePressed) {
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

			updateEntities(monsters, supermonsters, spawnTracks);
			displayBackgroundAndUI(window, backgroundSprite, pointTotal, healthDisplay, points, playerHealth);
			displayGameObjects(window, spawnTracks, playerHealth);

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