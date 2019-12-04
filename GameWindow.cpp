#include "GameWindow.hpp"

GameWindow::GameWindow(int width, int height, sf::Font appFont) {
	windowWidth = width;
	windowHeight = height;
	font = appFont;

	setupGameGraphics();
	setupGameLogic();
}

void GameWindow::initializeText(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color)
{
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(textSize);
	text.setFillColor(color);
	text.setPosition(yPosition, xPosition);
}

void GameWindow::setupGameLogic() {

	if (!buffer.loadFromFile("Pop.wav")) {
		cout << "Couldn't load the sound file" << endl;
	}
	popSound.setBuffer(buffer);

	playerHealth = 100;
	points = 0;

	positioner = 592;
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		spawnTracks[i] = SpawnTrack(positioner, (rand() % 2 + 1), (rand() % 250));
		positioner -= 128;
	}

	initializeText(healthDisplay, font, 18, 10, windowWidth - 200, "HEALTH: " + to_string(playerHealth), sf::Color::White);
	initializeText(pointTotal, font, 18, 10, 5, "SCORE: " + to_string(points), sf::Color::White);
	initializeText(gunpointNotFound, font, 26, (windowHeight / 2), (windowWidth / 3), "CANNOT LOCATE CONTROLLER", sf::Color::Yellow);
	//Monsters
	for (int i = 0; i < MONSTER_COUNT; i++) {
		monsters[i] = Monster(
			1, // health points
			10, // points per kill
			10, // damage dealt to player
			60, // hitbox radius
			monsterSprite
		);
	}
	//Supermonsters
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
	//Medpacks
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
	//Moneybags
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
}

int GameWindow::setupGameGraphics() {
	if (!backgroundTexture.loadFromFile("background.jpg")) {
		cout << "Couldn't load the background image" << endl;
		return -1;
	}
	if (!monsterTexture.loadFromFile("testmonster.png")) {
		cout << "Couldn't load the monster texture" << endl;
		return -2;
	}
	if (!supermonsterTexture.loadFromFile("supermonster.png")) {
		cout << "Couldn't load the super monster texture" << endl;
		return -3;
	}
	if (!medpackTexture.loadFromFile("medpack.png")) {
		cout << "Couldn't load the medpack texture" << endl;
		return -4;
	}
	if (!moneybagTexture.loadFromFile("moneybag.png")) {
		cout << "Couldn't load the moneybag texture" << endl;
		return -5;
	}

	backgroundSprite.setTexture(backgroundTexture);
	monsterSprite.setTexture(monsterTexture);
	supermonsterSprite.setTexture(supermonsterTexture);
	medpackSprite.setTexture(medpackTexture);
	moneybagSprite.setTexture(moneybagTexture);

	return 0;
}

void GameWindow::displayBackgroundAndUI(sf::RenderWindow& window,
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

void GameWindow::displayGameObjects(sf::RenderWindow& window, SpawnTrack(&spawnTracks)[SPAWN_TRACK_COUNT]) {
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		spawnTracks[i].update(playerHealth);
		spawnTracks[i].draw(window);
	}
}

bool GameWindow::checkForCollisions(WebcamControl& webcamThread) {
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		for (int j = 0; j < SPAWN_SOCKETS_PER_TRACK; j++) {
			if (spawnTracks[i].sockets[j].checkCollision(webcamThread.getX(), webcamThread.getY(), 30)) {
				int shotEffect1, shotEffect2;
				spawnTracks[i].sockets[j].registerShot(shotEffect1, shotEffect2);
				if (shotEffect1 <= 0) playerHealth -= shotEffect1;
				points += shotEffect2;
				return true;
			}
		}
	}
	return false;
}

void GameWindow::updateEntities() {
	for (int i = 0; i < MONSTER_COUNT; i++) {
		if (!monsters[i].checkMount() || monsters[i].hasCooldown() > 0) {
			int memoryLimiter = 0;
			while (true && memoryLimiter < 4) {
				memoryLimiter++;
				SpawnSocket& helper = spawnTracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
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
				SpawnSocket& helper = spawnTracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
				if (!helper.checkMount() && helper.isOutOfWindow()) {
					helper.mount(supermonsters[i]);

					break;
				}
			}
		}
	}

	for (int i = 0; i < MEDPACK_COUNT; i++) {
		if (!medpacks[i].checkMount() || medpacks[i].hasCooldown() > 0) {
			int memoryLimiter = 0;
			while (true && memoryLimiter < 4) {
				memoryLimiter++;
				SpawnSocket& helper = spawnTracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
				if (!helper.checkMount() && helper.isOutOfWindow()) {
					helper.mount(medpacks[i]);

					break;
				}
			}
		}
	}

	for (int i = 0; i < MONEYBAG_COUNT; i++) {
		if (!moneybags[i].checkMount() || moneybags[i].hasCooldown() > 0) {
			int memoryLimiter = 0;
			while (true && memoryLimiter < 4) {
				memoryLimiter++;
				SpawnSocket& helper = spawnTracks[rand() % SPAWN_TRACK_COUNT].sockets[rand() % SPAWN_SOCKETS_PER_TRACK];
				if (!helper.checkMount() && helper.isOutOfWindow()) {
					helper.mount(moneybags[i]);

					break;
				}
			}
		}
	}
}

void GameWindow::handleEvent(sf::Event event, bool& spacePressed, bool& playPressed, WebcamControl& webcamThread) {
	if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			if (checkForCollisions(webcamThread) && !spacePressed) {
				spacePressed = true;
				popSound.play();
				cout << "Bullseye!" << endl;
				//points += 10;
			}
			else if (!spacePressed && playPressed)
			{
				spacePressed = true;
				cout << "Miss! " << endl;
				points -= 1;
			}
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			playPressed = false;
		}
	}
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			spacePressed = false;
		}
	}
}

bool GameWindow::drawWindow(sf::RenderWindow& window, WebcamControl& webcamThread, sf::Sprite aimSprite)
{
	if(playerHealth <= 0) return true;
	updateEntities();
	displayBackgroundAndUI(window, backgroundSprite, pointTotal, healthDisplay, points, playerHealth);
	displayGameObjects(window, spawnTracks);

	if (webcamThread.getX() < 0 || webcamThread.getY() < 0) {
		window.draw(gunpointNotFound);
	}
	else {
		window.draw(aimSprite);
	}
	return false;
}