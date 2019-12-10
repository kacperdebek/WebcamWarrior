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
		SpawnSocket(int, int, int);
		void update(int&);
		void draw(sf::RenderWindow&);

		void mount(Monster&);
		void unmount();
		bool checkMount();
		string SpawnSocket::registerShot(int& shotDetails1, int& shotDetails2, int& posX, int& posY);

		bool checkCollision(int, int, int);
		bool isOutOfWindow();
		Monster& getMonster();
		int getPositionX();
		int getBaseline(); 
		void updateAnimation();
};
