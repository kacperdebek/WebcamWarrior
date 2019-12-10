#include "GameWindow.hpp"

GameWindow::GameWindow(int width, int height, sf::Font appFont) {
	srand(time(NULL));

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
	counter = 0;

	if (!shootSoundBuffer1.loadFromFile("flaunch.wav")) {
		cout << "Couldn't load the sound file" << endl;
	}
	shootSound1.setBuffer(shootSoundBuffer1);

	if (!shootSoundBuffer2.loadFromFile("rlaunch.wav")) {
		cout << "Couldn't load the sound file" << endl;
	}
	shootSound2.setBuffer(shootSoundBuffer2);

	shootSound1.setVolume(80);
	shootSound2.setVolume(80);

	playerHealth = 100;
	points = 0;

	positioner = 592;
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		spawnTracks[i] = SpawnTrack(positioner, (rand() % 2 + 1), (rand() % 250));
		positioner -= 128;
	}

	initializeText(healthDisplay, font, 25, 10, windowWidth - 150, "HEALTH: " + to_string(playerHealth), sf::Color::White);
	initializeText(pointTotal, font, 25, 10, 15, "SCORE: " + to_string(points), sf::Color::White);
	initializeText(gunpointNotFound, font, 40, (windowHeight / 2) - 50, (windowWidth / 3), "CANNOT LOCATE CONTROLLER", sf::Color::Yellow);
	//Monsters
	for (int i = 0; i < MONSTER_COUNT; i++) {
		monsters[i] = Monster(
			1, // health points
			10, // points per kill
			10, // damage dealt to player
			60, // hitbox radius
			monsterSprite,
			"monster_death.wav"
		);
		monsters[i].setCooldown(0 + rand() % 20);
	}
	//Supermonsters
	for (int i = 0; i < SUPERMONSTER_COUNT; i++) {
		for (int i = 0; i < SUPERMONSTER_COUNT; i++) {
			supermonsters[i] = Monster(
				2, // health points
				20, // points per kill
				15, // damage dealt to player
				60, // hitbox radius
				supermonsterSprite,
				"supermonster_death.wav"
			);
			supermonsters[i].setCooldown(300 + rand() % 700);
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
				medpackSprite,
				"Pop.wav"
			);
			medpacks[i].setCooldown(1500 + rand() % 3500);
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
				moneybagSprite,
				"Pop.wav"
			);
			moneybags[i].setCooldown(2500 + rand() % 4500);
		}
	}
}

int GameWindow::setupGameGraphics() {
	if (!backgroundTexture.loadFromFile("bgspritesheet.png")) {
		cout << "Couldn't load the background image" << endl;
		return -1;
	}
	/*
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
	*/
	if (!monsterTexture.loadFromFile("spritesheet.png")) {
		cout << "Couldn't load the monster texture" << endl;
		return -2;
	}
	if (!supermonsterTexture.loadFromFile("spritesheet.png")) {
		cout << "Couldn't load the super monster texture" << endl;
		return -3;
	}
	if (!medpackTexture.loadFromFile("spritesheet.png")) {
		cout << "Couldn't load the medpack texture" << endl;
		return -4;
	}
	if (!moneybagTexture.loadFromFile("spritesheet.png")) {
		cout << "Couldn't load the moneybag texture" << endl;
		return -5;
	}
	
	backgroundSprite.setTexture(backgroundTexture);
	monsterSprite.setTexture(monsterTexture);
	supermonsterSprite.setTexture(supermonsterTexture);
	medpackSprite.setTexture(medpackTexture);
	moneybagSprite.setTexture(moneybagTexture);

	backgroundRect = sf::IntRect(0, 0, 1280, 720);
	backgroundSprite.setTextureRect(backgroundRect);

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

	if(counter++ == 25) {
		if (backgroundRect.left == 1280) {
			backgroundRect.left = 0;
			backgroundRect.top += 720; 
			if (backgroundRect.top == (720 * 4)) {
				backgroundRect.top = 0;
			}
		}
		else backgroundRect.left += 1280;
		counter = 0;
	}

	backgroundSprite.setTextureRect(this->backgroundRect);

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

void GameWindow::updateAnimation() {
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		spawnTracks[i].updateAnimation();
	}
	/*
	if (animationCounter) animationRect.top += 128;
	else animationRect.top -= 128;
	
	cout << "1" << endl;

		if (animationRect.left == 384) {
			animationRect.left = 0;
			animationRect.top += 128;
			if (animationRect.top == 384) {
				animationRect.top = 0;
			}
		}
		else animationRect.left += 128;
		
	monsterSprite.setTextureRect(animationRect);
	supermonsterSprite.setTextureRect(animationRect);
	medpackSprite.setTextureRect(animationRect);
	moneybagSprite.setTextureRect(animationRect);

	animationCounter = !animationCounter;
	*/
}

bool GameWindow::checkForCollisions(WebcamControl& webcamThread) {
	for (int i = 0; i < SPAWN_TRACK_COUNT; i++) {
		for (int j = 0; j < SPAWN_SOCKETS_PER_TRACK; j++) {
			if (spawnTracks[i].sockets[j].checkCollision(webcamThread.getX(), webcamThread.getY(), 30)) {
				int shotEffect1, shotEffect2;

				string name = spawnTracks[i].sockets[j].registerShot(shotEffect1, shotEffect2);
				
				if (shotEffect1 <= 0) playerHealth -= shotEffect1;
				points += shotEffect2;

				if (!deathSoundBuffer.loadFromFile(name)) {
					cout << "Couldn't load the sound file" << endl;
				}
				deathSound.setBuffer(deathSoundBuffer);
				deathSound.play();

				return true;
			}
		}
	}
	return false;
}

void GameWindow::updateEntities() {
	for (int i = 0; i < MONSTER_COUNT; i++) {
		if (!monsters[i].checkMount() && !monsters[i].hasCooldown()) {
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
		if (!supermonsters[i].checkMount() && !supermonsters[i].hasCooldown()) {
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
		if (!medpacks[i].checkMount() && !medpacks[i].hasCooldown()) {
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
		if (!moneybags[i].checkMount() && !moneybags[i].hasCooldown()) {
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
			//shootSound.play();
			GunShot();

			if (checkForCollisions(webcamThread) && !spacePressed) {
				spacePressed = true;
				//popSound.play();
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

bool GameWindow::drawWindow(sf::RenderWindow& window, WebcamControl& webcamThread, sf::Sprite aimSprite, sf::Clock &animationTimer)
{
	if (animationTimer.getElapsedTime().asMilliseconds() > 150) {
		updateAnimation();
	}
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

void GameWindow::GunShot() {
	if (rand() % 2) shootSound1.play();
	else shootSound2.play();
}