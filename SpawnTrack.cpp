#include "SpawnTrack.h"

SpawnTrack::SpawnTrack() {
	this->speed = 0;
	this->baseline = 0;
	for (int i = 0; i < SPAWN_SOCKETS_PER_TRACK; i++) {
		this->sockets[i] = SpawnSocket();
	}
}

SpawnTrack::SpawnTrack(int startY, int speed, int shift) {
	this->speed = speed;
	this->baseline = startY;
	cout << "Spawn track speed and baseline coord:" << this->speed << this->baseline << "\n";

	int positioner = -1800 - shift;
	for (int i = 0; i < SPAWN_SOCKETS_PER_TRACK; i++) {
		this->sockets[i] = SpawnSocket(this->baseline, this->speed, positioner);
		positioner += 158;
	}
}

void SpawnTrack::update() {
	for (int i = 0; i < SPAWN_SOCKETS_PER_TRACK; i++) {
		this->sockets[i].update();
	}
}

void SpawnTrack::draw(sf::RenderWindow& window) {
	for (int i = 0; i < SPAWN_SOCKETS_PER_TRACK; i++) {
		this->sockets[i].draw(window);
	}
}
