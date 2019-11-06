#include "SpawnSocket.h"

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

void SpawnSocket::update() {
	this->positionX += speed;
	if (this->positionX > 1430) {
		this->positionX = -150;
		if (this->isMounted && this->mountedMonster != NULL) {
			this->unmount();
		}
	}
	if (isMounted) {
		this->getMonster().updatePosition(this->positionX, this->baseline);
	};
}

void SpawnSocket::draw(sf::RenderWindow& window) {
	//sf::RectangleShape rectangle;
	//rectangle.setSize(sf::Vector2f(128, 128));
	//rectangle.setOutlineColor(sf::Color::Red);
	//rectangle.setOutlineThickness(5);
	//rectangle.setPosition(this->positionX, this->baseline);

	if (this->isMounted) {
		//this->getMonster().drawHitbox(window);
		this->getMonster().draw(window);
	}
	//else {
	//	window.draw(rectangle);
	//}
}

void SpawnSocket::mount(Monster& monster) {
	this->isMounted = true;
	this->mountedMonster = &monster;
	this->getMonster().setMounted();
}

void SpawnSocket::unmount() {
	cout << "Spawn socket unmount checkpoint\n";
	cout << "Position of the socket: " << this->positionX << "\n";
	this->getMonster().unmount();
	this->mountedMonster = NULL;
	this->isMounted = false;
}

bool SpawnSocket::checkMount() {
	return this->isMounted;
}

bool SpawnSocket::checkCollision(int aimX, int aimY, int aimRadius) {
	if (this->isMounted) {
		if (this->positionX == aimX) {
			cout << "Coords monster: " << this->positionX << ", " << this->baseline << "\n";
			cout << "Coords aim: " << aimX << ", " << aimY << "\n";
			return (abs(this->baseline + aimY) <= aimRadius + this->getMonster().getHitboxRadius());
		}
		if (this->baseline == aimY) {
			cout << "Coords monster: " << this->positionX << ", " << this->baseline << "\n";
			cout << "Coords aim: " << aimX << ", " << aimY << "\n";
			return (abs(this->positionX + aimX) <= aimRadius + this->getMonster().getHitboxRadius());
		}

		cout << "Coords monster: " << this->positionX << ", " << this->baseline << "\n";
		cout << "Coords aim: " << aimX << ", " << aimY << "\n";
		cout << "Estimated distance: " << sqrt(pow(abs(aimX - this->positionX), 2) + pow(abs(aimY - this->baseline), 2)) << "\n";

		if (sqrt(pow(abs(aimX - this->positionX), 2) + pow(abs(aimY - this->baseline), 2)) <= aimRadius + this->getMonster().getHitboxRadius()) {
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