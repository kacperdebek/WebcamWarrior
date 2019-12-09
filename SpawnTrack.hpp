#pragma once
#include "SpawnSocket.hpp"

class SpawnTrack
{
private:
	int baseline;
	int speed;
public:
	SpawnSocket sockets[SPAWN_SOCKETS_PER_TRACK];

	SpawnTrack();
	SpawnTrack(int, int, int);
	void update(int&);
	void draw(sf::RenderWindow&);
	void updateAnimation();
};

