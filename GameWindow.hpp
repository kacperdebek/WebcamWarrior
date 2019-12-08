#pragma once
#include "WebcamControl.hpp"
#include "SpawnTrack.hpp"
#include "Monster.hpp"

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

	sf::Text healthDisplay;
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
	
	sf::Sprite backgroundSprite;
	sf::Sprite monsterSprite;
	sf::Sprite supermonsterSprite;
	sf::Sprite medpackSprite;
	sf::Sprite moneybagSprite;

	int playerHealth;
	int points;
	int positioner;
	int windowWidth;
	int windowHeight;
	bool gameOverFlag;

public:
	GameWindow(int, int, sf::Font);
	void setupGameLogic();
	int setupGameGraphics();
	void initializeText(sf::Text&, sf::Font&, int, int, int, const String&, const sf::Color&);
	void displayBackgroundAndUI(sf::RenderWindow&, sf::Sprite&, sf::Text&, sf::Text&, int, int);
	void displayGameObjects(sf::RenderWindow&, SpawnTrack(&)[SPAWN_TRACK_COUNT]);
	bool checkForCollisions(WebcamControl&);
	void updateEntities();
	void handleEvent(sf::Event, bool&, bool&, WebcamControl&);
	bool drawWindow(sf::RenderWindow&, WebcamControl&, sf::Sprite);
	void GunShot();
};