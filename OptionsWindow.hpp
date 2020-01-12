#pragma once
#include "Menu.hpp"
#include "SliderSFML.hpp"
#include "GenericCHeader.hpp"

class OptionsWindow {
private:
	float currSliderValue;
	float oldSliderValue;

	sf::Text sliderText;
	SliderSFML slider;
public:
	OptionsWindow(int width, int height, sf::Font& font, WebcamControl& webcamThread);
	void handleEvent(sf::Event event, bool& optionsPressed);
	void drawWindow(sf::RenderWindow& window, WebcamControl& webcamThread, Menu& mainMenu);
	void initializeText(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color);
};