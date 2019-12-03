#include "SpawnSocket.hpp"

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
			playerHealth -= this->getMonster().getDamage();
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

int* SpawnSocket::registerShot() {
	int shotDetails[2];
	shotDetails[0] = this->getMonster().getDamage();
	shotDetails[1] = this->getMonster().getPoints();
	if (this->getMonster().handleShot()) this->unmount();
	return shotDetails;
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