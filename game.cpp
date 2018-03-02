#include "game.h"

Game::Game(sf::RenderWindow& win)
{
    window=&win;
    txtLoader.load();
    txtLoader.initialize(world.getPlayer());
    view.setCenter(world.getPlayer().getPosition().x+BLOCK_SIZE/2,world.getPlayer().getPosition().y+BLOCK_SIZE/2);
    view.setSize(sf::Vector2f(1920/2,1080/2));
    window->setView(view);
}

void Game::update()
{
    evHandler.checkEvents(*window);
    world.update();
    view.setCenter(center(world.getPlayer()));
    window->setView(view);
    world.generateChunks();
}

void Game::draw()
{
    window->clear();

    world.draw(*window);


    window->display();
}
