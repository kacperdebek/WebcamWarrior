#include "SpawnSocket.hpp"
#include <vector>

SpawnSocket::SpawnSocket() {
	this->baseline = 0;
	this->speed = 0;
	this->positionX = 0;
	this->isMounted = false;
}

SpawnSocket::SpawnSocket(int baseline, int speed, int positionX) {
	this->baseline = baseline;
	this->speed = speed;
	this->positionX = positionX;
	this->isMounted = false;
}

Monster& SpawnSocket::getMonster() {
	return *(this->mountedMonster);
}

void SpawnSocket::update(int& playerHealth) {
	this->positionX += speed;
	if (this->positionX > 1290) {
		this->positionX = -150;
		if (this->isMounted && this->mountedMonster != NULL) {
			if(this->getMonster().getDamage() > 0) playerHealth -= this->getMonster().getDamage();
			this->unmount();
		}
	}
	if (isMounted) {
		this->getMonster().updatePosition(this->positionX, this->baseline);
	};
}

void SpawnSocket::draw(sf::RenderWindow& window) {
	if (this->isMounted) {
		this->getMonster().draw(window);
	}
}

void SpawnSocket::mount(Monster& monster) {
	this->isMounted = true;
	this->mountedMonster = &monster;
	this->getMonster().setMounted();
}

void SpawnSocket::unmount() {
	this->getMonster().unmount();
	this->mountedMonster = NULL;
	this->isMounted = false;
}

bool SpawnSocket::checkMount() {
	return this->isMounted;
}

string SpawnSocket::registerShot(int& shotDetails1, int& shotDetails2) {
	shotDetails1 = this->getMonster().getDamage();
	shotDetails2 = this->getMonster().getPoints();
	if (this->getMonster().handleShot()) {
		string temp = this->getMonster().getDeathSound();
		this->unmount();
		return temp;
	}
	return this->getMonster().getDeathSound();
}

bool SpawnSocket::checkCollision(int aimX, int aimY, int aimRadius) {
	if (this->isMounted) {
		if (this->positionX == aimX) {
			return (abs(this->baseline + aimY) <= aimRadius + this->getMonster().getHitboxRadius());
		}
		if (this->baseline == aimY) {
			return (abs(this->positionX + aimX) <= aimRadius + this->getMonster().getHitboxRadius());
		}

		if (sqrt(pow(abs(aimX - this->positionX - 64), 2) + pow(abs(aimY - this->baseline - 64), 2)) <= aimRadius + this->getMonster().getHitboxRadius()) {
			return true;
		}
	}
	return false;
}

bool SpawnSocket::isOutOfWindow() {
	return (this->positionX <= -128);
}

int SpawnSocket::getBaseline() {
	return this->baseline;
}

int SpawnSocket::getPositionX() {
	return this->positionX;
}

void SpawnSocket::updateAnimation() {
	this->getMonster().updateSprite();
}
