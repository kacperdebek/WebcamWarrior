#pragma once
#include "SpawnSocket.h"

class SpawnTrack
{
private:
	int baseline;
	int speed;
	SpawnSocket sockets[8];
public:
	SpawnTrack();
	SpawnTrack(int);
	void update();
	void draw(sf::RenderWindow&);
};

