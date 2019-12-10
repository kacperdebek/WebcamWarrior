#include "Explosion.hpp"

Explosion::Explosion(int posX, int posY) {
	counter = 0;

	this->spriteRect = sf::IntRect(-128, 0, 128, 128);
	this->posX = posX;
	this->posY = posY;
}

Explosion::~Explosion() {}

bool Explosion::updateFrame() {
	if (counter++ == 4) {
		if (this->spriteRect.left == (128 * 3)) {
			this->spriteRect.left = 0;
			this->spriteRect.top += 128;
			if (this->spriteRect.top == (128 * 3)) {// && (spriteRect.left == (128*2))) {
				return false;
			}
		}
		else this->spriteRect.left += 128;
		counter = 0;
	}
	return true;
}

sf::IntRect Explosion::getRect() {
	return this->spriteRect;
}

int Explosion::getPositionX() {
	return posX;
}

int Explosion::getPositionY() {
	return posY;
}
