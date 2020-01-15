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
	SpawnTrack(int startY, int speed, int shift);
	void update(int& playerHealth);
	void draw(sf::RenderWindow& window);
};

