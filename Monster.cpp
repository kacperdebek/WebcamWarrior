#include "Monster.hpp"
Monster::Monster() {
	this->isMounted = false;
	this->cooldown = 0;
	this->baseCooldown = 0;
}

Monster::Monster(int health, int points, int damage, int hitboxRadius, sf::Sprite& sprite, string sound) {
	this->totalHealth = health;
	this->health = health;
	this->damage = damage;
	this->pointsValue = points;
	this->cooldown = 0;
	this->baseCooldown = 0;
	this->isMounted = false;
	this->hitboxRadius = hitboxRadius;

	this->rectSourceSprite = sf::IntRect(0, 0, 128, 128);

	this->sprite = sprite;
	this->sprite.setTextureRect(this->rectSourceSprite);

	this->hitbox = sf::CircleShape();
	this->hitbox.setRadius(hitboxRadius);
	this->hitbox.setFillColor(sf::Color::Red);

	this->deathSound.assign(sound);
	this->animationCounter = 0;
}


void Monster::updatePosition(int x, int y) {
	this->centerX = x;
	this->centerY = y;
}

void Monster::draw(sf::RenderWindow& window) {
	if (animationCounter++ == 20) {
		if (this->rectSourceSprite.left == 128) {
			this->rectSourceSprite.left = 0;
		}
		else this->rectSourceSprite.left += 128;
		animationCounter = 0;
	}

	this->sprite.setTextureRect(this->rectSourceSprite);
	this->sprite.setPosition(this->centerX, this->centerY);
	window.draw(this->sprite);
}

void Monster::drawHitbox(sf::RenderWindow& window) {
	this->hitbox.setPosition(this->centerX, this->centerY);
	window.draw(this->hitbox);
}

void Monster::setMounted() {
	this->health = this->totalHealth;
	this->isMounted = true;
	this->cooldown = 0;
}

void Monster::unmount() {
	this->isMounted = false;
	this->cooldown = this->baseCooldown;
}

bool Monster::checkMount() {
	return this->isMounted;
}

bool Monster::handleShot() {
	if (--this->health <= 0) {
		this->health = this->totalHealth;
		return true;
	}
	return false;
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

void Monster::setCooldown(int cd) {
	this->baseCooldown = cd;
	this->cooldown = cd;
}

int Monster::getDamage() {
	return this->damage;
}

int Monster::getPoints() {
	return this->pointsValue;
}

string Monster::getDeathSound() {
	return this->deathSound;
}

