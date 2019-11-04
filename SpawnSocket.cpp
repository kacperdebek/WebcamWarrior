#include "SpawnSocket.h"

SpawnSocket::SpawnSocket() {
	this->baseline = 0;
	this->speed = 0;
	this->positionX = 0;
}

SpawnSocket::SpawnSocket(int baseline, int speed, int positionX) {
	this->baseline = baseline;
	this->speed = speed;
	this->positionX = positionX;
}

void SpawnSocket::update() {
	this->positionX += speed;
	if (this->positionX > 1430) {
		this->positionX = -150;
	}
}

void SpawnSocket::draw(sf::RenderWindow& window) {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(128, 128));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(this->positionX, this->baseline);

	window.draw(rectangle);
}