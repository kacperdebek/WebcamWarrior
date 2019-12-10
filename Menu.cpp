#include "Menu.hpp"


Menu::Menu(float width, float height, vector<string> labelList, sf::Color mainColor, sf::Color selectedColor) {
	if (!font.loadFromFile("Aileenation.ttf")) {
		cout << "Couldn't load the font" << endl;
		return;
	}
	if (!this->menuBackgroundTexture.loadFromFile("menubackground.jpg")) {
		cout << "Couldn't load menu background image" << endl;
		return;
	}
	if (!this->menuButtonTexture.loadFromFile("menubutton.png")) {
		cout << "Couldn't load menu background image" << endl;
		return;
	}
	if (!this->menuTheme.openFromFile("main_theme.ogg")) {
		cout << "Couldn't load menu music" << endl;
		return;
	}
	menuTheme.setVolume(70);
	this->width = width;
	this->height = height;
	this->selectedColor = selectedColor;
	this->mainColor = mainColor;
	this->menuBackgroundSprite.setTexture(this->menuBackgroundTexture);
	this->menuButtonSprite.setTexture(this->menuButtonTexture);
	this->menuButtonSprite.setOrigin(sf::Vector2f(70.f, 30.f));
	this->numOfLabels = (int)labelList.size();
	menu = new sf::Text[numOfLabels];
	for (int i = 0; i < numOfLabels; i++) {
		menu[i].setFont(font);
		menu[i].setColor(mainColor);
		menu[i].setString(labelList.at(i));
		const sf::FloatRect bounds(menu[i].getLocalBounds());
		const sf::Vector2f box(menuButtonTexture.getSize());
		menu[i].setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
		menu[i].setPosition(sf::Vector2f((this->width / 2) - 115, (this->height / (numOfLabels + 1) * (i+1)) + 50));
	}
	selectedItemIndex = -1;
}
Menu::~Menu()
{
	delete[] menu;
}

void Menu::draw(sf::RenderWindow &window) {
	bool itemIsSelected = false;
	window.draw(menuBackgroundSprite);
	for (int i = 0; i < numOfLabels; i++) {
		menuButtonSprite.setPosition(sf::Vector2f((this->width / 2) - 50, this->height / (numOfLabels + 1) * (i + 1) + 75));
		window.draw(menuButtonSprite);
		if((menu[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
			menu[i].setColor(selectedColor);
			selectedItemIndex = i;
			itemIsSelected = true;
		}
		else {
			menu[i].setColor(mainColor);
		}
		window.draw(menu[i]);
	}
	if (!itemIsSelected)
		selectedItemIndex = -1;
	itemIsSelected = false;
	 
}
sf::Sprite Menu::getBackground() {
	return this->menuBackgroundSprite;
}

void Menu::playMenuTheme() {
	this->menuTheme.play();
	this->menuTheme.setLoop(true);
}

void Menu::stopMenuTheme() {
	this->menuTheme.stop();
}