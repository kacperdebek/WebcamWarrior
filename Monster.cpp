#include "Monster.h"
Monster::Monster() {
	this->isMounted = false;
	this->cooldown = 0;
}

Monster::Monster(int health, int points, int hitboxRadius, sf::Sprite& sprite){
	this->cooldown = 0;
	this->isMounted = false;
	this->hitboxRadius = hitboxRadius;
	this->sprite = sprite;
	this->hitbox = sf::CircleShape();
	this->hitbox.setRadius(hitboxRadius);
	this->hitbox.setFillColor(sf::Color::Red);
}


void Monster::updatePosition(int x, int y) {
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

void Monster::setMounted() {
	this->isMounted = true;
	this->cooldown = 0;
}

void Monster::unmount() {
	this->isMounted = false;
	this->cooldown = 10;
}

bool Monster::checkMount() {
	return this->isMounted;
}

int Monster::getHitboxRadius() {
	return this->hitboxRadius;
}

bool Monster::hasCooldown() {
	if (this->cooldown > 0) {
		cooldown--;
		return true;
	}
	return false;
}
