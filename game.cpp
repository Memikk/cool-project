#include "game.h"

Game::Game(sf::RenderWindow& win)
{
    worldGenNoise.reseed(rand()*48325673492);
    objectNoise.reseed(rand()*53580345638);
    cout<<"wylosowano seed mapy"<<endl;

    txtLoader = new TextureLoader();
    world = new World(txtLoader);
    evHandler = new EventHandler(win);
    iface = new Interface();
    view = new sf::View();
    cout<<"txt loader i world stworzony"<<endl;

    window=&win;
    cout<<"ustawiono wskaznik na okno"<<endl;

    txtLoader->load();
    cout<<"zaladowano textury"<<endl;
    txtLoader->setPlayerTexture(world->getPlayer());
    cout<<"ustawiono teksture gracza"<<endl;

    view->setCenter(world->getPlayer().getPosition().x+BLOCK_SIZE/2,world->getPlayer().getPosition().y+BLOCK_SIZE/2);
    view->setSize(sf::Vector2f(1920/2,1080/2));
    window->setView(*view);
    cout<<"gra stworzona"<<endl;

    world->generateChunks();
}

void Game::update()
{
    //cout<<"GENERUJE CHUNKI"<<endl;
    std::thread chunkGeneratingThread(&World::generateChunks,world);

    //cout<<"SPRAWDZAM EVENTY"<<endl;
    evHandler->checkEvents(*world,*view);

    //cout<<"AKTUALIZUJE SWIAT"<<endl;
    world->update(*window);

    //cout<<"USTAWIAM WIDOK"<<endl;
    view->setCenter(vh::center(world->getPlayer()));
    window->setView(*view);

    //cout<<"DOLACZAM WATEK"<<endl;
    chunkGeneratingThread.join();
}

void Game::draw()
{
    //cout<<"NOWY WATEK"<<endl;
    std::thread fpsThread(&Interface::update,iface);

    //cout<<"CZYSZCZENIE"<<endl;
    window->clear();

    //cout<<"WRZUCANIE JEDNOSTEK"<<endl;
    world->spawnEntities();

    //cout<<"RYSOWANIE SWIATA"<<endl;
    world->draw(*window);

    //cout<<"DOLACZENIE WATKU FPS"<<endl;
    fpsThread.join();

    iface->draw(world->getPlayer(),*window);

    //cout<<"POKAZYWANIE"<<endl;
    window->display();
}
