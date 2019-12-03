#include <iostream>
#include "WebcamControl.hpp"
#include "Menu.hpp"
#include "SliderSFML.hpp"
#include "GameWindow.hpp"
#include "OptionsWindow.hpp"

#define SPAWN_DELAY 10
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

void initializeTexts(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color)
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
	webcamThread.setThreshold(200);
	thread.launch();

	sf::Text gunpointNotFound;
	sf::Font font;
	
	sf::Texture aimTexture;
	sf::Sprite aimSprite;

	// Graphics setup
	if (!font.loadFromFile("Arial.ttf")) {
		cout << "Couldn't load the font" << endl;
		return -1;
	}
	if (!aimTexture.loadFromFile("aim.png")) {
		cout << "Couldn't load the aim texture" << endl;
		return -1;
	}
	/*if (!monsterTexture.loadFromFile("testmonster.png")) {
		cout << "Couldn't load the monster texture" << endl;
		return -1;
	}
	if (!supermonsterTexture.loadFromFile("supermonster.png")) {
		cout << "Couldn't load the super monster texture" << endl;
		return -1;
	}
	if (!medpackTexture.loadFromFile("medpack.png")) {
		cout << "Couldn't load the medpack texture" << endl;
		return -1;
	}
	if (!moneybagTexture.loadFromFile("moneybag.png")) {
		cout << "Couldn't load the moneybag texture" << endl;
		return -1;
	}*/


	aimSprite.setTexture(aimTexture);
	/*monsterSprite.setTexture(monsterTexture);
	supermonsterSprite.setTexture(supermonsterTexture);
	medpackSprite.setTexture(medpackTexture);
	moneybagSprite.setTexture(moneybagTexture);
	
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

	Monster medpacks[MEDPACK_COUNT];
	for (int i = 0; i < MEDPACK_COUNT; i++) {
		for (int i = 0; i < MEDPACK_COUNT; i++) {
			medpacks[i] = Monster(
				1, // health points
				0, // points per kill
				-20, // damage dealt to player
				60, // hitbox radius
				medpackSprite
			);
			medpacks[i].setCooldown(150000);
		}
	}

	Monster moneybags[MONEYBAG_COUNT];
	for (int i = 0; i < MONEYBAG_COUNT; i++) {
		for (int i = 0; i < MONEYBAG_COUNT; i++) {
			moneybags[i] = Monster(
				1, // health points
				100, // points per kill
				0, // damage dealt to player
				60, // hitbox radius
				moneybagSprite
			);
			moneybags[i].setCooldown(250000);
		}
	}
	
	initializeText(healthDisplay, font, 18, 10, WINDOW_WIDTH - 200, "HEALTH: " + to_string(playerHealth), sf::Color::White);
	initializeText(pointTotal, font, 18, 10, 5, "SCORE: " + to_string(points), sf::Color::White);*/
	initializeTexts(gunpointNotFound, font, 26, (WINDOW_HEIGHT / 2), (WINDOW_WIDTH / 3), "CANNOT LOCATE CONTROLLER", sf::Color::Yellow);
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Pop.wav")) {
		cout << "Couldn't load the sound file" << endl;
		return -1;
	}
	sf::Sound popSound;
	popSound.setBuffer(buffer);

	sf::Time dt;
	bool spacePressed = false;
	bool playPressed = false;
	bool optionsPressed = false;
	vector<string> mainMenuLabels = { "Play", "Options", "Exit" };
	vector<string> optionsMenuLabels = { "Template" };
	Menu mainMenu(WINDOW_WIDTH, WINDOW_HEIGHT, mainMenuLabels, sf::Color::White, sf::Color::Red);
	Menu optionsMenu(WINDOW_WIDTH, WINDOW_HEIGHT, optionsMenuLabels, sf::Color::White, sf::Color::Red);
	SliderSFML slider(WINDOW_WIDTH / 2 - 130, WINDOW_HEIGHT / 2, 255);
	slider.create(0, 255);
	slider.setSliderValue(webcamThread.getThreshold());
	static std::once_flag onceFlag;

	GameWindow gameWindow(WINDOW_WIDTH, font);
	OptionsWindow optionsWindow(WINDOW_WIDTH, WINDOW_HEIGHT, font, webcamThread);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (playPressed) { //gamewindow
				gameWindow.handleEvent(event, spacePressed, playPressed, webcamThread);
			}
			else if (optionsPressed) { //optionswindow
				/*if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Keyboard::Escape)
						optionsPressed = false;
				}*/
				optionsWindow.handleEvent(event, optionsPressed);
			}
			else { //mainmenuwindow
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Mouse::Left)
				{
					switch (mainMenu.GetPressedItem())
					{
					case 0:
						playPressed = true;
						break;
					case 1:
						sf::sleep(sf::milliseconds(200));
						optionsPressed = true;
						break;
					case 2:
						thread.terminate();
						window.close();
						break;
					default:
						break;
					}
				}
			}
		}

		aimSprite.setPosition(webcamThread.getX() - (aimSprite.getGlobalBounds().width / 2), webcamThread.getY() - (aimSprite.getGlobalBounds().height / 2));
		if (playPressed)
		{
			gameWindow.drawWindow(window, webcamThread, aimSprite);
		}
		else if (optionsPressed)
		{
			optionsWindow.drawWindow(window, webcamThread, mainMenu, aimSprite);
		}/*{
			currSliderValue = slider.getSliderValue();
			if (currSliderValue != oldSliderValue)
				webcamThread.setThreshold(currSliderValue);
			window.clear();
			window.draw(mainMenu.getBackground());
			window.draw(sliderText);
			slider.draw(window);
			window.draw(aimSprite); //TODO: do spakowania w jedn? funkcj?
			oldSliderValue = currSliderValue;
		}*/
		else
		{		
			window.clear();
			mainMenu.draw(window, webcamThread);
			window.draw(aimSprite);
		}

		window.display();
	}

	return 0;
}