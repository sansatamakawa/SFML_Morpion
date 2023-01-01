#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Res.h"
#include "player.h"

class Homepage
{
public:
	Homepage(Res& _res);
	int Interaction(sf::Event& _event, Player _player[], bool& _bHomepage);
	void Draw(sf::RenderWindow& _window);
private:
	sf::Font font;
	sf::Text text;
	std::vector<std::vector<sf::RectangleShape>> matriceRShape;
private:
	const int X = 2;
	const int Y = 2;
	bool bTest = true;
private:
	Res* res;
};

