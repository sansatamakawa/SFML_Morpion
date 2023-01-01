#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Grid.h"
#include "Homepage.h"
#include "Res.h"
#include "player.h"

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update();
	void render();
private:
	sf::RenderWindow window;
	float dt;
	bool bHomepage;
private:
	Grid grid;
	Homepage *homepage;
	Res res;
};
