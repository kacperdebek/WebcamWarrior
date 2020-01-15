#pragma once
#include "WebcamControl.hpp"
#include "SpawnTrack.hpp"
#include "Monster.hpp"
#include "Explosion.hpp"

#define MONSTER_COUNT 5
#define SUPERMONSTER_COUNT 2
#define MEDPACK_COUNT 2
#define MONEYBAG_COUNT 4

class GameWindow {
private:
	sf::Font font;

	sf::SoundBuffer deathSoundBuffer;
	sf::SoundBuffer shootSoundBuffer1;
	sf::SoundBuffer shootSoundBuffer2;

	sf::Sound deathSound;
	sf::Sound shootSound1;
	sf::Sound shootSound2;

	sf::Text pointTotal;
	sf::Text gunpointNotFound;

	Monster monsters[MONSTER_COUNT];
	Monster supermonsters[SUPERMONSTER_COUNT];
	Monster medpacks[MEDPACK_COUNT];
	Monster moneybags[MONEYBAG_COUNT];
	SpawnTrack spawnTracks[SPAWN_TRACK_COUNT];

	sf::Texture backgroundTexture;
	sf::Texture monsterTexture;
	sf::Texture supermonsterTexture;
	sf::Texture medpackTexture;
	sf::Texture moneybagTexture;
	sf::Texture explosionTexture;
	sf::Texture lifeBarTexture;
	
	sf::IntRect backgroundRect;

	sf::Sprite backgroundSprite;
	sf::Sprite lifeBarSprite;

	list<Explosion> explosions;

	int playerHealth;
	int points;
	int positioner;
	int windowWidth;
	int windowHeight;
	bool gameOverFlag;
	int counter;
	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;
	sf::IntRect gameOverRect;

	void setupGameover();
	void setupSound();
	void setupLogic();
	void setupExplosions();
	void setupUI();
	void setupBackground();

	void setupMonsters();
	void setupSupermonsters();
	void setupMedpacks();
	void setupMoneybags();

	void initializeText(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color);
	void displayBackgroundAndUI(sf::RenderWindow& window);
	void displayGameObjects(sf::RenderWindow& window);
	bool checkForCollisions(WebcamControl& webcamThread);
	void updateEntities();
	void playGunshotSound();
	void updateLifeBar();

public:
	GameWindow(int width, int height, sf::Font appFont);
	
	void handleEvent(sf::Event event, bool& spacePressed, bool& playPressed, WebcamControl& webcamThread);
	bool drawWindow(sf::RenderWindow& window, WebcamControl& webcamThread, sf::Sprite aimSprite, sf::Clock& animationTimer);
};