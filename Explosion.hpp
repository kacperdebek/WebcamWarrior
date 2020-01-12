#pragma once
#include "GenericCHeader.hpp"
#include "SFMLHeader.hpp"

class Explosion {
private:
	sf::IntRect spriteRect;
	int posX, posY;
	int counter;
public:
	Explosion(int posX, int posY);
	~Explosion();
	bool updateFrame();
	sf::IntRect getRect();
	int getPositionX();
	int getPositionY();
};