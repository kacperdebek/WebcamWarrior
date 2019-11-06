#pragma once
#include "WebcamControl.hpp"

class Monster
{
private:
	int centerX;
	int centerY;
	int hitboxRadius;

	int cooldown;
	bool isMounted;

	sf::Sprite sprite;
	sf::RectangleShape border;
	sf::CircleShape hitbox;

	int health;
	int pointsValue;
public:

	Monster();
	Monster(int, int, int, sf::Sprite&);
	void updatePosition(int, int);
	void drawHitbox(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	void unmount();
	bool checkMount();
	int getHitboxRadius();
	bool hasCooldown();
	void setMounted();

};
