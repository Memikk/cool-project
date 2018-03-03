#include "game.h"

Game::Game(sf::RenderWindow& win)
{
    txtLoader = new TextureLoader();
    world = new World(txtLoader);
    cout<<"txt loader i world stworzony"<<endl;

    window=&win;
    cout<<"ustawiono wskaznik na okno"<<endl;

    txtLoader->load();
    cout<<"zaladowano textury"<<endl;
    txtLoader->setPlayerTexture(world->getPlayer());
    cout<<"ustawiono teksture gracza"<<endl;

    view.setCenter(world->getPlayer().getPosition().x+BLOCK_SIZE/2,world->getPlayer().getPosition().y+BLOCK_SIZE/2);
    view.setSize(sf::Vector2f(1920/2,1080/2));
    window->setView(view);
    cout<<"gra stworzona"<<endl;
}

void Game::update()
{
    //cout<<"GENERUJE CHUNKI"<<endl;
    world->generateChunks();

    //cout<<"SPRAWDZAM EVENTY"<<endl;
    evHandler.checkEvents(*window);

    //cout<<"AKTUALIZUJE SWIAT"<<endl;
    world->update();

    //cout<<"USTAWIAM WIDOK"<<endl;
    view.setCenter(center(world->getPlayer()));
    window->setView(view);
}

void Game::draw()
{
    window->clear();

    world->draw(*window);


    window->display();
}
