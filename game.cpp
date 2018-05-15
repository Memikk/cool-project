#include "game.h"

Menu::Menu()
{
    tmp = new sf::Texture();
    tmp->loadFromFile("resources/textures/menuFrame.png");
    frame.setTexture(*tmp);
    frame.setPosition(sf::Vector2f(0,0));

    background.setFillColor(sf::Color(222,191,94));
    background.setSize(sf::Vector2f(1920,1080));
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(frame);
}

Game::Game(sf::RenderWindow& win)
{
    worldGenNoise.reseed(rand()*48325673492);
    objectNoise.reseed(rand()*53580345638);
    cout<<"wylosowano seed mapy"<<endl;

    txtLoader = new TextureLoader();
    txtLoader->load();
    cout<<"zaladowano textury"<<endl;

    saver = new Saver();
    evHandler = new EventHandler(win);
    iface = new Interface(txtLoader);
    world = new World(txtLoader,iface,saver);
    view = new sf::View();
    cout<<"txt loader i world stworzony"<<endl;

    window=&win;
    cout<<"ustawiono wskaznik na okno"<<endl;

    menu = new Menu();

    txtLoader->setPlayerTexture(world->getPlayer());
    cout<<"ustawiono teksture gracza"<<endl;

    iface->update(world->getPlayer(),*window);

}

void Game::update()
{
    evHandler->checkEvents(*world,*view,gs);
    if(gs==INGAME)
    {
        //cout<<"GENERUJE CHUNKI"<<endl;
        std::thread chunkGeneratingThread(&World::generateChunks,world);

        //cout<<"AKTUALIZUJE SWIAT"<<endl;
        world->update(*window);
        iface->setTime(world->gameTime);
        iface->setDays(world->days);

        std::thread upThread(&Interface::update,iface,world->getPlayer(),*window);

        //cout<<"USTAWIAM WIDOK"<<endl;
        view->setCenter(vh::center(world->getPlayer()));
        window->setView(*view);

        //cout<<"DOLACZAM WATEK"<<endl;
        upThread.join();
        chunkGeneratingThread.join();
    }
    else
    {

    }
}

void Game::draw()
{
    //cout<<"CZYSZCZENIE"<<endl;
    window->clear();

    if(gs==INGAME)
    {
        world->spawnEntities();

        world->draw(*window);

        iface->draw(world->getPlayer(),*window);
    }
    else if(gs==MENU)
    {
        menu->draw(*window);
    }

    //cout<<"POKAZYWANIE"<<endl;
    window->display();
}
