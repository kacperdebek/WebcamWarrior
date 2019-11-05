#pragma once
#include "WebcamControl.hpp"
#include "Monster.h"

class SpawnSocket
{
	private:
		int positionX;
		int baseline;
		int speed;
		bool isMounted;
		Monster mountedMonster;
	public:
		SpawnSocket();
		SpawnSocket(int, int, int);
		void update();
		void draw(sf::RenderWindow&);
		void mount(Monster&);
		void unmount();
		bool checkMount();
		bool checkCollision(int, int, int);
};
