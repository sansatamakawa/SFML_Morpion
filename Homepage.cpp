#include "Homepage.h"
#include "parameters.h"

using namespace std;

Homepage::Homepage(Res& _res)
{
	font.loadFromFile("Font/Akashi/akashi.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(50);
	text.setString("Joueur 1 choisit");
	text.setPosition(sf::Vector2f((WINDOW_X / 2) - text.getGlobalBounds().width/2, (WINDOW_Y / 2) - text.getGlobalBounds().height/2 - 500));

	res = &_res;
;
	string cImages[4];
	cImages[0] = "aizen.bmp";
	cImages[1] = "cellophané.jpg";
	cImages[2] = "sansatamakawa.png";
	cImages[3] = "tanjiro.jpg";

	int k = 0;
	sf::Vector2f posBase = sf::Vector2f(WINDOW_X/2, WINDOW_Y/2);
	for (int i = 0; i < X; i++)
	{
		matriceRShape.push_back(std::vector<sf::RectangleShape>());
		for (int j = 0; j < Y; j++)
		{
			matriceRShape[i].push_back(sf::RectangleShape());
			matriceRShape[i][j].setSize(sf::Vector2f(100, 100));
			matriceRShape[i][j].setPosition(sf::Vector2f(posBase.x + (i*100) - 100, posBase.y + (j*100) - 100));
			matriceRShape[i][j].setTexture(&_res.getTexture(cImages[k]));
			k++;
		}
	}
}

int Homepage::Interaction(sf::Event& _event, Player _player[], bool& _bHomepage)
{
	if (_event.type == sf::Event::MouseButtonReleased)
	{
		if (_event.key.code == sf::Mouse::Left)
		{
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();

			for (int i = 0; i < X; i++)
			{
				for (int j = 0; j < Y; j++)
				{
					if (matriceRShape[i][j].getGlobalBounds().contains(mousePos))
					{
						if (bTest)
						{
							_player[0].texture = *matriceRShape[i][j].getTexture();
							text.setString("Joueur 2 choisit");
							bTest = false;
						}
						else
						{
							_player[1].texture = *matriceRShape[i][j].getTexture();
							_bHomepage = false;
						}
					}
				}
			}
		}
	}
	return 0;
}

void Homepage::Draw(sf::RenderWindow& _window)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			_window.draw(matriceRShape[i][j]);
		}
	}
	_window.draw(text);
}
