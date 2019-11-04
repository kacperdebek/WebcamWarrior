#pragma once
#include "SpawnSocket.h"

class Entity
{
private:
	bool isMounted;
	SpawnSocket socket;

	sf::Sprite sprite;
	sf::RectangleShape border;
	sf::CircleShape hitbox;
};

