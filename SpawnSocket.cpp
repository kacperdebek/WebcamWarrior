#include "SpawnSocket.h"

SpawnSocket::SpawnSocket() {
	this->baseline = 0;
	this->speed = 0;
	this->positionX = 0;
	this->isMounted = false;
	this->mountedMonster = Monster();
}

SpawnSocket::SpawnSocket(int baseline, int speed, int positionX) {
	this->baseline = baseline;
	this->speed = speed;
	this->positionX = positionX;
	this->isMounted = false;
}

void SpawnSocket::update() {
	this->positionX += speed;
	if (this->positionX > 1430) {
		this->positionX = -150;
	}
	if (isMounted) {
		this->mountedMonster.updatePosition(this->positionX, this->baseline);
	};
}

void SpawnSocket::draw(sf::RenderWindow& window) {
	//sf::RectangleShape rectangle;
	//rectangle.setSize(sf::Vector2f(128, 128));
	//rectangle.setOutlineColor(sf::Color::Red);
	//rectangle.setOutlineThickness(5);
	//rectangle.setPosition(this->positionX, this->baseline);

	if (this->isMounted) {
		this->mountedMonster.drawHitbox(window);
		this->mountedMonster.draw(window);
	}
	//else {
	//	window.draw(rectangle);
	//}
}

void SpawnSocket::mount(Monster& monster) {
	this->isMounted = true;
	this->mountedMonster = monster;
}

void SpawnSocket::unmount() {
	this->mountedMonster.unmount();
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
			return (abs(this->baseline + aimY) <= aimRadius + this->mountedMonster.getHitboxRadius());
		}
		if (this->baseline == aimY) {
			cout << "Coords monster: " << this->positionX << ", " << this->baseline << "\n";
			cout << "Coords aim: " << aimX << ", " << aimY << "\n";
			return (abs(this->positionX + aimX) <= aimRadius + this->mountedMonster.getHitboxRadius());
		}

		cout << "Coords monster: " << this->positionX << ", " << this->baseline << "\n";
		cout << "Coords aim: " << aimX << ", " << aimY << "\n";
		cout << "Estimated distance: " << sqrt(pow(abs(aimX - this->positionX), 2) + pow(abs(aimY - this->baseline), 2)) << "\n";

		if (sqrt(pow(abs(aimX - this->positionX), 2) + pow(abs(aimY - this->baseline), 2)) <= aimRadius + this->mountedMonster.getHitboxRadius()) {
			return true;
		}
	}
	return false;
}