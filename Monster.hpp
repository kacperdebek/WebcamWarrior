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
	Monster(int health, int points, int damage, int hitboxRadius, sf::Sprite& sprite, string sound);
	void updatePosition(int x, int y);
	void drawHitbox(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void unmount();
	bool checkMount();
	bool handleShot();

	int getHitboxRadius();
	bool hasCooldown();
	void setCooldown(int cd);
	void setMounted();
	int getDamage();
	int getPoints();
	string getDeathSound();
};
