#pragma once
#include "WebcamControl.hpp"

class SpawnSocket
{
	private:
		int positionX;
		int baseline;
		int speed;
	public:
		SpawnSocket();
		SpawnSocket(int, int, int);
		void update();
		void draw(sf::RenderWindow&);
};

