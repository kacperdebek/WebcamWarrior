#pragma once
#include <SFML\Graphics.hpp>
#include "GenericCHeader.hpp"

class SliderSFML
{
	sf::RectangleShape slider;
	sf::RectangleShape axis;
	sf::Font font;
	sf::Text text;
	int minValue;
	int maxValue;
	int xCord;
	int yCord;
	int axisWidth;
	int axisHeight;
	int sliderWidth;
	int sliderHeight;
	float sliderValue;
	void logic(sf::RenderWindow& window);
public:
	SliderSFML();
	SliderSFML(int x, int y, int length);
	void setSlider(int x, int y, int length);
	sf::Text returnText(int x, int y, std::string z, int fontSize);
	void create(int min, int max);
	
	float getSliderValue();
	void setSliderValue(float newValue);
	void setSliderPercentValue(float newPercentValue);
	void draw(sf::RenderWindow & window);
};

