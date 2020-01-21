#include <iostream>
#include "WebcamControl.hpp"
#include "Menu.hpp"
#include "GameWindow.hpp"
#include "OptionsWindow.hpp"

#define SPAWN_DELAY 10
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

void initializeTexts(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color) {
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(textSize);
	text.setFillColor(color);
	text.setPosition(yPosition, xPosition);
}
void showMessageOrAim(WebcamControl& webcamThread, sf::RenderWindow& window, sf::Text notFoundMessage, sf::Sprite aimSprite) {
	if (webcamThread.getX() < 0 || webcamThread.getY() < 0) {
		window.draw(notFoundMessage);
	}
	else {
		window.draw(aimSprite);
	}
}
int main()
{
	srand(time(NULL));
	sf::Clock animationTimer;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Strzelnica");
	window.setFramerateLimit(60);

	WebcamControl webcamThread;
	sf::Thread thread(&WebcamControl::run, &webcamThread);
	webcamThread.setThreshold(200);
	thread.launch();

	sf::Text gunpointNotFound;
	sf::Text finalScore;
	sf::Font font;
	
	sf::Texture aimTexture;
	sf::Sprite aimSprite;


	if (!font.loadFromFile("DisposableDroidBB.ttf")) {
		cout << "Couldn't load the font" << endl;
		return -1;
	}
	if (!aimTexture.loadFromFile("aim.png")) {
		cout << "Couldn't load the aim texture" << endl;
		return -1;
	}

	aimSprite.setTexture(aimTexture);
	int score = 0;
	initializeTexts(gunpointNotFound, font, 26, (WINDOW_HEIGHT / 2), (WINDOW_WIDTH / 3), "CANNOT LOCATE CONTROLLER", sf::Color::Yellow);
	initializeTexts(finalScore, font, 36, (WINDOW_HEIGHT / 4), (WINDOW_WIDTH / 2) - 100, "Final score: " + score, sf::Color::Yellow);
	sf::Time dt;
	bool spacePressed = false;
	bool playPressed = false;
	bool optionsPressed = false;
	bool gameOver = false;
	vector<string> mainMenuLabels = { "PLAY", "OPTIONS", "EXIT" };
	vector<string> gameOverMenuLabels = { "PLAY AGAIN", "QUIT GAME" };
	Menu mainMenu(WINDOW_WIDTH, WINDOW_HEIGHT, mainMenuLabels, sf::Color::White, sf::Color::Red);
	Menu gameOverMenu(WINDOW_WIDTH, WINDOW_HEIGHT, gameOverMenuLabels, sf::Color::White, sf::Color::Red);

	GameWindow newGameWindow(WINDOW_WIDTH, WINDOW_HEIGHT, font);
	OptionsWindow newOptionsWindow(WINDOW_WIDTH, WINDOW_HEIGHT, font, webcamThread);
	GameWindow gameWindow = newGameWindow;
	OptionsWindow optionsWindow = newOptionsWindow;
	
	mainMenu.playMenuTheme();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (gameOver) {
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Mouse::Left) {
					switch (gameOverMenu.getPressedItem()) {
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
			if (playPressed) { 
				gameWindow.handleEvent(event, spacePressed, playPressed, webcamThread);
			}
			else if (optionsPressed) { 
				optionsWindow.handleEvent(event, optionsPressed);
			}
			else { 
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Mouse::Left) {
					switch (mainMenu.getPressedItem()) {
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
			gameOverMenu.draw(window);
			finalScore.setString("Final score: " + to_string(gameWindow.getPoints()));
			window.draw(finalScore);
		}
		else if (playPressed) {
			window.clear();
			showMessageOrAim(webcamThread, window, gunpointNotFound, aimSprite);
			gameOver = gameWindow.drawWindow(window, webcamThread, aimSprite, animationTimer);
		}
		else if (optionsPressed) {
			optionsWindow.drawWindow(window, webcamThread, mainMenu);
		}
		else {		
			window.clear();
			mainMenu.draw(window);
		}
		window.display();
	}
	return 0;
}