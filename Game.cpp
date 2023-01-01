#include "Game.h"
#include "parameters.h"

using namespace std;

Game::Game() : dt(0), bHomepage(true)
{
    window.create(sf::VideoMode(WINDOW_X, WINDOW_Y), "Morpion du futur", sf::Style::Fullscreen);
    homepage = new Homepage(res);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
            window.close();

        if (bHomepage)
        {
            homepage->Interaction(event, grid.player, bHomepage);
        }
        else
        {
            grid.Interaction(event);
        }
    }
}

void Game::update()
{

}

void Game::render()
{
	window.clear(sf::Color(120, 120, 120));
    if (bHomepage)
    {
        homepage->Draw(window);
    }
    else
    {
        grid.Draw(window);
    }
    window.display();
}
