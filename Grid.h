#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "player.h"

class Grid
{
public:
	Grid();
	void FillBox(int _index);
	void CheckIfWin();
	int CheckIfNul();
	int Interaction(sf::Event& _event);
	void Draw(sf::RenderWindow& _window);
private:
	sf::RectangleShape grid;
	std::vector<sf::RectangleShape> vLine;
	std::vector<sf::RectangleShape> vBox;
	std::vector<int> nBoxFilled;
	std::vector<std::vector<int>> winCompo;
private:
	int length;
	int thickness;
	int around;
	int sizeBox;
private:
	bool changeTurn;
	bool gameFinished;
private:
	sf::Font font;
	sf::Text textWin;
public:
	Player player[2];
};
