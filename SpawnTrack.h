#pragma once
#include "SpawnSocket.h"

class SpawnTrack
{
private:
	int baseline;
	int speed;
public:
	SpawnSocket sockets[10];

	SpawnTrack();
	SpawnTrack(int, int, int);
	void update();
	void draw(sf::RenderWindow&);
};

