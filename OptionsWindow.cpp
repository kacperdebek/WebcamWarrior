#include "OptionsWindow.hpp"

OptionsWindow::OptionsWindow(int width, int height, sf::Font& font, WebcamControl& webcamThread) {
	initializeText(sliderText, font, 26, (width / 2) - 80, (width / 3) + 90, "Threshold adjustment", sf::Color::White);
	slider.setSlider(width / 2 - 130, height / 2, 255);
	slider.create(0, 255);
	slider.setSliderValue(webcamThread.getThreshold());
	oldSliderValue = slider.getSliderValue();
}

void OptionsWindow::handleEvent(sf::Event event, bool& optionsPressed) {
	if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			optionsPressed = false;
	}
}

void OptionsWindow::drawWindow(sf::RenderWindow& window, WebcamControl& webcamThread, Menu& mainMenu, sf::Sprite& aimSprite) {
	if (currSliderValue != oldSliderValue)
		webcamThread.setThreshold(currSliderValue);
	window.clear();
	window.draw(mainMenu.getBackground());
	window.draw(sliderText);
	slider.draw(window);
	window.draw(aimSprite); //TODO: do spakowania w jedn? funkcj?
	oldSliderValue = currSliderValue;
}

void OptionsWindow::initializeText(sf::Text& text, sf::Font& font, int textSize, int xPosition, int yPosition, const String& label, const sf::Color& color)
{
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(textSize);
	text.setFillColor(color);
	text.setPosition(yPosition, xPosition);
}
