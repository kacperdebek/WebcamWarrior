#include "Monster.h"
Monster::Monster() {
	this->isMounted = false;
}

Monster::Monster(int health, int points, int hitboxRadius, sf::Sprite& sprite){
	this->isMounted = false;
	this->hitboxRadius = hitboxRadius;
	this->sprite = sprite;
	this->hitbox = sf::CircleShape();
	this->hitbox.setRadius(hitboxRadius);
	this->hitbox.setFillColor(sf::Color::Red);
}


void Monster::updatePosition(int x, int y) {
	if (cooldown > 0) {
		cooldown--;
	}
	this->centerX = x;
	this->centerY = y;
}

void Monster::draw(sf::RenderWindow& window) {
	this->sprite.setPosition(this->centerX, this->centerY);
	window.draw(this->sprite);
}

void Monster::drawHitbox(sf::RenderWindow& window) {
	this->hitbox.setPosition(this->centerX, this->centerY);
	window.draw(this->hitbox);
}

void Monster::unmount() {
	this->isMounted = 0;
	this->cooldown = 100;
}

bool Monster::checkMount() {
	return this->isMounted;
}

int Monster::getHitboxRadius() {
	return this->hitboxRadius;
}