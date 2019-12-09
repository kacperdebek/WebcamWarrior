#pragma once
#include "SFMLHeader.hpp"
#include "GenericCHeader.hpp"

class Monster
{
private:
	int centerX;
	int centerY;
	int hitboxRadius;

	int baseCooldown;
	int cooldown;
	bool isMounted;

	sf::Sprite sprite;
	sf::RectangleShape border;
	sf::CircleShape hitbox;
	
	int animationCounter;
	sf::IntRect rectSourceSprite;
	
	int totalHealth;
	int health;
	int pointsValue;
	int damage;

	string deathSound;
public:

	Monster();
	Monster(int, int, int, int, sf::Sprite&, string);
	void updatePosition(int, int);
	void drawHitbox(sf::RenderWindow&);
	void draw(sf::RenderWindow&);

	void unmount();
	bool checkMount();
	bool handleShot();
	void updateSprite();

	int getHitboxRadius();
	bool hasCooldown();
	void setCooldown(int);
	void setMounted();
	int getDamage();
	int getPoints();
	string getDeathSound();
};
