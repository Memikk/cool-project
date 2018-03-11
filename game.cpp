#include "game.h"

Game::Game(sf::RenderWindow& win)
{
    txtLoader = new TextureLoader();
    world = new World(txtLoader);
    cout<<"txt loader i world stworzony"<<endl;

    font.loadFromFile("arial.ttf");
    fps.setFont(font);
    fps.setCharacterSize(14);
    fps.setColor(sf::Color(255,200,50));
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(2);

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

    world->generateChunks();
}

void Game::update()
{
    //cout<<"GENERUJE CHUNKI"<<endl;
    std::thread chunkGeneratingThread(&World::generateChunks,world);

    //cout<<"SPRAWDZAM EVENTY"<<endl;
    evHandler.checkEvents(*window);

    //cout<<"AKTUALIZUJE SWIAT"<<endl;
    world->update();

    //cout<<"USTAWIAM WIDOK"<<endl;
    view.setCenter(vh::center(world->getPlayer()));
    window->setView(view);

    chunkGeneratingThread.join();
}

void Game::draw()
{
    std::thread fpsThread(&Game::countFPS,this);

    window->clear();

    world->draw(*window);

    fpsThread.join();
    window->draw(fps);

    window->display();
}

void Game::countFPS()
{
    if(fpsClock.getElapsedTime().asSeconds() >= 1.f)
    {
			mFps=mFrame;
			mFrame=0;
			fpsClock.restart();
    }

    ++mFrame;

    fps.setString("FPS="+to_string(mFps));
    fps.setPosition(world->getPlayer().getPosition().x-460,world->getPlayer().getPosition().y-260);
}
