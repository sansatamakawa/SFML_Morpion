#include "Grid.h"
#include "parameters.h"

using namespace std;

Grid::Grid() : length(900), thickness(4), around(16), sizeBox(300), changeTurn(true), gameFinished(false)
{
	grid.setSize(sf::Vector2f(length + around, length + around));
	grid.setPosition(sf::Vector2f(WINDOW_X/2 - grid.getSize().x/2, WINDOW_Y / 2 - grid.getSize().y / 2));

	sf::RectangleShape rShapeLine;
	rShapeLine.setFillColor(sf::Color::Black);

	sf::RectangleShape rShapeBox;
	rShapeBox.setFillColor(sf::Color(225, 225, 225));
	rShapeBox.setSize(sf::Vector2f(sizeBox, sizeBox));

	int nbLines = 8;
	int nbBoxes = 9;

	for (int i = 0; i < nbLines; i++)
	{
		vLine.push_back(rShapeLine);
	}

	for (int i = 0; i < nbBoxes; i++)
	{
		vBox.push_back(rShapeBox);

		nBoxFilled.push_back(0);
	}

	string composition = "246048036147258012345678";
	int ii = 0;
	for (int i = 0; i < 8; i++)
	{
		winCompo.push_back(std::vector<int>());
		for (int j = 0; j < 3; j++)
		{
			winCompo[i].push_back(int());
			winCompo[i][j] = composition[ii] - '0';
			ii++;
		}
	}

	#ifndef LINES
	// Autour
	vLine[0].setSize(sf::Vector2f(length + around, thickness));
	vLine[0].setPosition(sf::Vector2f(grid.getPosition().x, grid.getPosition().y));

	vLine[1].setSize(sf::Vector2f(length + around, thickness));
	vLine[1].setPosition(sf::Vector2f(grid.getPosition().x, grid.getPosition().y + grid.getSize().y - vLine[1].getSize().y));

	vLine[2].setSize(sf::Vector2f(thickness, length + around));
	vLine[2].setPosition(sf::Vector2f(grid.getPosition().x, grid.getPosition().y));

	vLine[3].setSize(sf::Vector2f(thickness, length + around));
	vLine[3].setPosition(sf::Vector2f(grid.getPosition().x + grid.getSize().x - vLine[3].getSize().x, grid.getPosition().y));

	//// Dedans
	vLine[4].setSize(sf::Vector2f(length + around, thickness));
	vLine[4].setPosition(sf::Vector2f(grid.getPosition().x, grid.getPosition().y + (sizeBox + thickness)));

	vLine[5].setSize(sf::Vector2f(length + around, thickness));
	vLine[5].setPosition(sf::Vector2f(grid.getPosition().x, grid.getPosition().y + (2 * (sizeBox + thickness))));

	vLine[6].setSize(sf::Vector2f(thickness, length + around));
	vLine[6].setPosition(sf::Vector2f(grid.getPosition().x + (sizeBox + thickness), grid.getPosition().y));

	vLine[7].setSize(sf::Vector2f(thickness, length + around));
	vLine[7].setPosition(sf::Vector2f(grid.getPosition().x + (2 * (sizeBox + thickness)), grid.getPosition().y));
	#endif

	#ifndef BOXES
	int racineArray = 3;
	int j = 0;
	int k = 0;
	for (int i = 0; i < vBox.size(); i++)
	{
		if (j < 3)
		{
			vBox[i].setPosition(sf::Vector2f(grid.getPosition().x + thickness + (j * (sizeBox + thickness)), grid.getPosition().y + thickness + (k * (sizeBox + thickness))));
			j++;
		}
		else
		{
			k++;
			j = 0;
			vBox[i].setPosition(sf::Vector2f(grid.getPosition().x + thickness + (j * (sizeBox + thickness)), grid.getPosition().y + thickness + (k * (sizeBox + thickness))));
			j++;
		}
	}
	#endif

	font.loadFromFile("Font/Arial/arial.ttf");
	textWin.setFont(font);
	textWin.setCharacterSize(50);
	textWin.setFillColor(sf::Color::White);
}

void Grid::FillBox(int _index)
{
	if (changeTurn) // TRUE = PLAYER_1
	{
		changeTurn = false;
		vBox[_index].setTexture(&player[0].texture);
		nBoxFilled[_index] = 1;
	}
	else // FALSE = PLAYER_2
	{
		changeTurn = true;
		vBox[_index].setTexture(&player[1].texture);
		nBoxFilled[_index] = 2;
	}
}

void Grid::CheckIfWin()
{
	int diagonales = 2;
	int verticales = 3;
	int horizontales = 3;
	int totalPossibilities = diagonales + verticales + horizontales;

	int player_1 = 1;
	int player_2 = 2;
	for (int i = 0; i < totalPossibilities; i++) // 8
	{
		if (nBoxFilled[winCompo[i][0]] == player_1 && nBoxFilled[winCompo[i][1]] == player_1 && nBoxFilled[winCompo[i][2]] == player_1)
		{
			textWin.setString("WIN JOUEUR 1");
			textWin.setPosition(sf::Vector2f(WINDOW_X / 2 - textWin.getGlobalBounds().width / 2, textWin.getPosition().y));
			gameFinished = true;
		}
		else if (nBoxFilled[winCompo[i][0]] == player_2 && nBoxFilled[winCompo[i][1]] == player_2 && nBoxFilled[winCompo[i][2]] == player_2)
		{
			textWin.setString("WIN JOUEUR 2");
			textWin.setPosition(sf::Vector2f(WINDOW_X / 2 - textWin.getGlobalBounds().width / 2, textWin.getPosition().y));
			gameFinished = true;
		}
	}
}

int Grid::CheckIfNul()
{
	for (int i = 0; i < nBoxFilled.size(); i++)
	{
		if (nBoxFilled[i] == 0)
		{
			return 0;
		}
	}
	textWin.setString("NUL");
	textWin.setPosition(sf::Vector2f(WINDOW_X / 2 - textWin.getGlobalBounds().width / 2, textWin.getPosition().y));
	gameFinished = true;
}

int Grid::Interaction(sf::Event& _event)
{
	int nReturn = -1;

	if (!gameFinished)
	{
		if (_event.type == sf::Event::MouseButtonReleased)
		{
			if (_event.key.code == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();

				for (int i = 0; i < vBox.size(); i++)
				{
					if (vBox[i].getGlobalBounds().contains(mousePos) && nBoxFilled[i] == 0)
					{
						FillBox(i);
						CheckIfNul();
						CheckIfWin();
					}
				}
			}
		}
	}

	return nReturn;
}

void Grid::Draw(sf::RenderWindow& _window)
{
	_window.draw(grid);
	for (sf::RectangleShape& rShape : vLine)
		_window.draw(rShape);
	for (sf::RectangleShape& rShape : vBox)
		_window.draw(rShape);
	if (gameFinished)
		_window.draw(textWin);
}
