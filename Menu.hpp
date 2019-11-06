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

private:
	int selectedItemIndex;
	int numOfLabels;
	sf::Font font;
	sf::Text *menu;

};