#include "Menu.hpp"


Menu::Menu(float width, float height, vector<string> labelList, sf::Color mainColor, sf::Color selectedColor)
{
	if (!font.loadFromFile("Gamefont.ttf"))
	{
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
	this->width = width;
	this->height = height;
	this->menuBackgroundSprite.setTexture(this->menuBackgroundTexture);
	this->menuButtonSprite.setTexture(this->menuButtonTexture);
	this->menuButtonSprite.setOrigin(sf::Vector2f(70.f, 30.f));
	this->numOfLabels = (int)labelList.size();
	menu = new sf::Text[numOfLabels];
	for (int i = 0; i < numOfLabels; i++)
	{
		menu[i].setFont(font);
		i == 0 ? menu[i].setColor(selectedColor) : menu[i].setColor(mainColor);
		menu[i].setString(labelList.at(i));
		const sf::FloatRect bounds(menu[i].getLocalBounds());
		const sf::Vector2f box(menuButtonTexture.getSize());
		menu[i].setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
		menu[i].setPosition(sf::Vector2f((this->width / 2) - 115, (this->height / (numOfLabels + 1) * (i+1)) - 25));
	}
	selectedItemIndex = 0;
}
Menu::~Menu()
{
	delete[] menu;
}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(menuBackgroundSprite);
	for (int i = 0; i < numOfLabels; i++)
	{
		menuButtonSprite.setPosition(sf::Vector2f((this->width / 2) - 50, this->height / (numOfLabels + 1) * (i + 1)));
		window.draw(menuButtonSprite);
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = numOfLabels - 1;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < numOfLabels)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
sf::Sprite Menu::getBackground()
{
	return this->menuBackgroundSprite;
}