#include "Entity.h"

Entity::Entity() {
	this->isMounted = false;
}

Entity::Entity(int hitboxRadius, sf::Sprite& sprite) {
	this->hitboxRadius = hitboxRadius;
	this->sprite = sprite;
	this->hitbox = sf::CircleShape();
	this->hitbox.setRadius(hitboxRadius);
	this->hitbox.setOutlineColor(sf::Color::Red);
}

bool Entity::checkCollision(int aimX, int aimY, int aimRadius) {
	if (this->centerX == aimX) {
		return (abs(this->centerY - aimY) <= aimRadius + this->hitboxRadius);
	}
	if (this->centerY == aimY) {
		return (abs(this->centerX - aimX) <= aimRadius + this->hitboxRadius);
	}
	return sqrt(pow(abs(aimX + this->centerX), 2) + pow(abs(aimY + this->centerY), 2)) <= aimRadius + this->hitboxRadius;
}

void Entity::updatePosition(int x, int y) {
	this->centerX = x;
	this->centerY = y;
}

void Entity::draw(sf::RenderWindow& window) {
	this->sprite.setPosition(this->centerX, this->centerY);
	window.draw(this->sprite);
}

void Entity::draw(sf::RenderWindow& window) {
	this->hitbox.setPosition(this->centerX, this->centerY);
	window.draw(this->hitbox);
}