#pragma once
#include "SFML/Graphics.hpp"
#include <mutex>
#include <iostream>
using namespace std;
class Menu
{
public:
	Menu(float width, float height, vector<string> labelList, sf::Color mainColor, sf::Color selectedColor);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	sf::Sprite getBackground();

private:
	int selectedItemIndex;
	int numOfLabels;
	int width;
	int height;
	sf::Font font;
	sf::Text *menu;
	sf::Sprite menuBackgroundSprite;
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuButtonSprite;
	sf::Texture menuButtonTexture;
};