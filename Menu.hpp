#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <mutex>
#include <iostream>
#include "WebcamControl.hpp"
using namespace std;
class Menu
{
public:
	Menu(float width, float height, vector<string> labelList, sf::Color mainColor, sf::Color selectedColor);
	~Menu();
	void draw(sf::RenderWindow &window);
	int GetPressedItem() { return selectedItemIndex; }
	sf::Sprite getBackground();
	void playMenuTheme();
	void stopMenuTheme();

private:
	int selectedItemIndex;
	int numOfLabels;
	int width;
	int height;
	sf::Color selectedColor;
	sf::Color mainColor;
	sf::Font font;
	sf::Text *menu;
	sf::Sprite menuBackgroundSprite;
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuButtonSprite;
	sf::Texture menuButtonTexture;
	sf::Music menuTheme;
};