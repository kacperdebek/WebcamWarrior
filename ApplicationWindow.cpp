#include <iostream>
#include "WebcamControl.hpp"
#include "Menu.hpp"
//#include "SliderSFML.hpp"
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


	if (!font.loadFromFile("Arial.ttf")) {
		cout << "Couldn't load the font" << endl;
		return -1;
	}
	if (!aimTexture.loadFromFile("aim.png")) {
		cout << "Couldn't load the aim texture" << endl;
		return -1;
	}

	aimSprite.setTexture(aimTexture);

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
	bool gameOver = false;
	vector<string> mainMenuLabels = { "Play", "Options", "Exit" };
	vector<string> optionsMenuLabels = { "Template" };
	vector<string> gameOverMenuLabels = { "Play again", "Quit game" };
	Menu mainMenu(WINDOW_WIDTH, WINDOW_HEIGHT, mainMenuLabels, sf::Color::White, sf::Color::Red);
	Menu optionsMenu(WINDOW_WIDTH, WINDOW_HEIGHT, optionsMenuLabels, sf::Color::White, sf::Color::Red);
	Menu gameOverMenu(WINDOW_WIDTH, WINDOW_HEIGHT, gameOverMenuLabels, sf::Color::White, sf::Color::Red);
	static std::once_flag onceFlag;

	GameWindow newGameWindow(WINDOW_WIDTH, font);
	OptionsWindow newOptionsWindow(WINDOW_WIDTH, WINDOW_HEIGHT, font, webcamThread);
	GameWindow gameWindow = newGameWindow;
	OptionsWindow optionsWindow = newOptionsWindow;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (gameOver) {
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Mouse::Left)
				{
					switch (gameOverMenu.GetPressedItem())
					{
					case 0:
						gameWindow = newGameWindow;
						optionsWindow = newOptionsWindow;
						gameOver = false;
						playPressed = true;
						optionsPressed = false;
						break;
					case 1:
						thread.terminate();
						window.close();
						break;
					default:
						break;
					}
				}
			}

			if (playPressed) { //gamewindow
				gameWindow.handleEvent(event, spacePressed, playPressed, webcamThread);
			}
			else if (optionsPressed) { //optionswindow
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
		if (gameOver) {
			window.clear();
			gameOverMenu.draw(window, webcamThread);
			window.draw(aimSprite);
		}
		else if (playPressed)
		{
			gameOver = gameWindow.drawWindow(window, webcamThread, aimSprite);
			if (gameOver) {
				window.clear();
				gameOverMenu.draw(window, webcamThread);
				window.draw(aimSprite);
			}
		}
		else if (optionsPressed)
		{
			optionsWindow.drawWindow(window, webcamThread, mainMenu, aimSprite);
		}
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