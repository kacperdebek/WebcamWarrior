#pragma once
#include "SpawnSocket.h"

class SpawnTrack
{
private:
	int baseline;
	int speed;
	SpawnSocket sockets[10];
public:
	SpawnTrack();
	SpawnTrack(int, int, int);
	void update();
	void draw(sf::RenderWindow&);
};

