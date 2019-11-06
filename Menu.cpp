#include "Menu.hpp"


Menu::Menu(float width, float height, vector<string> labelList, sf::Color mainColor, sf::Color selectedColor)
{
	if (!font.loadFromFile("Arial.ttf"))
	{
		cout << "Couldn't load the font" << endl;
		return;
	}
	this->numOfLabels = (int)labelList.size();
	menu = new sf::Text[numOfLabels];
	for (int i = 0; i < numOfLabels; i++)
	{
		menu[i].setFont(font);
		i == 0 ? menu[i].setColor(selectedColor) : menu[i].setColor(mainColor);
		menu[i].setString(labelList.at(i));
		menu[i].setPosition(sf::Vector2f((width / 2) - 50, height / (numOfLabels + 1) * (i+1)));
	}
	selectedItemIndex = 0;
}
Menu::~Menu()
{
	delete[] menu;
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < numOfLabels; i++)
	{
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