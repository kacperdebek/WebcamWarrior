#pragma once
#include "GenericCHeader.hpp"
#include "Monster.hpp"

#define SPAWN_TRACK_COUNT 5
#define SPAWN_SOCKETS_PER_TRACK 10

class SpawnSocket
{
	private:
		int positionX;
		int baseline;
		int speed;
		bool isMounted;
		Monster* mountedMonster;
	public:
		SpawnSocket();
		SpawnSocket(int baseline, int speed, int positionX);
		void update(int& playerHealth);
		void draw(sf::RenderWindow& window);

		void mount(Monster& monster);
		void unmount();
		bool checkMount();
		string SpawnSocket::registerShot(int& shotDetails1, int& shotDetails2, int& posX, int& posY);

		bool checkCollision(int aimX, int aimY, int aimRadius);
		bool isOutOfWindow();
		Monster& getMonster();
		int getPositionX();
		int getBaseline(); 
};
