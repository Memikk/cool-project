#include "game.h"

Menu::Menu()
{
    menuFrame = new sf::Texture();
    menuFrame->loadFromFile("resources/textures/menuFrame.png");
    escMenuTexture = new sf::Texture();
    escMenuTexture->loadFromFile("resources/textures/escmenu.png");
    frame.setTexture(*menuFrame);
    frame.setPosition(sf::Vector2f(0,0));
    escMenu.setTexture(*escMenuTexture);
    escMenu.setPosition(sf::Vector2f(0,0));
    escMenu.setScale(0.5,0.5);

    background.setFillColor(sf::Color(222,191,94));
    background.setSize(sf::Vector2f(1920,1080));

    contBox.setPosition(690,350);
    newBox.setPosition(690,515);
    exitBox.setPosition(690,680);
    contBox.setSize(sf::Vector2f(535,125));
    newBox.setSize(sf::Vector2f(535,125));
    exitBox.setSize(sf::Vector2f(535,125));
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(frame);
}

void Menu::drawEscMenu(sf::RenderWindow& window)
{
    escMenu.setPosition(window.getView().getCenter().x-vh::getSize(escMenu).x/2,window.getView().getCenter().y-vh::getSize(escMenu).y/2);
    contBox.setPosition(window.getView().getCenter().x-125,window.getView().getCenter().y-70);
    contBox.setSize(sf::Vector2f(250,70));
    newBox.setPosition(window.getView().getCenter().x-125,window.getView().getCenter().y+10);
    newBox.setSize(sf::Vector2f(250,70));

    window.draw(escMenu);
}

Game::Game(sf::RenderWindow& win)
{
    fstream save1seed("save1seed.txt",ios::in);
    string temp;
    getline(save1seed,temp);
    if(temp=="")
    {
        save1seed.close();
        fstream s1s("save1seed.txt");
        cerr<<"pusty seed"<<endl;
        int s1=rand()*483232;
        int s2=rand()*535638;
        worldGenNoise.reseed(s1);
        objectNoise.reseed(s2);
        cerr<<s1<<" "<<std::to_string(s1)<<endl;
        s1s<<std::to_string(s1)<<endl<<std::to_string(s2)<<endl;
    }
    else
    {
        cerr<<"wczytuje seed"<<endl;
        worldGenNoise.reseed(stoi(temp));
        getline(save1seed,temp);
        objectNoise.reseed(stoi(temp));
    }
    save1seed.close();

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

    fstream playerSave("save1player.txt");
    float x,y;
    playerSave>>x>>y;
    world->getPlayer().setPosition(x,y);
    cout<<"wczytano pozycje gracza"<<endl;

    iface->update(world->getPlayer(),*window);

}

void Game::update()
{
    vector<sf::RectangleShape> boxes;
    boxes.push_back(menu->contBox);
    boxes.push_back(menu->newBox);
    boxes.push_back(menu->exitBox);
    evHandler->checkEvents(*world,*view,gs,boxes);
    if(gs==INGAME||gs==ESCWINDOW)
    {
        //cout<<"GENERUJE CHUNKI"<<endl;
        std::thread chunkGeneratingThread(&World::generateChunks,world);

        //cout<<"AKTUALIZUJE SWIAT"<<endl;
        world->update(*window);
        iface->setTime(world->gameTime);
        iface->setDays(world->days);

        std::thread upThread(&Interface::update,iface,world->getPlayer(),*window);
        //iface->update(world->getPlayer(),*window);
        //cout<<"USTAWIAM WIDOK"<<endl;
        view->setCenter(vh::center(world->getPlayer()));
        window->setView(*view);

        //cout<<"DOLACZAM WATEK"<<endl;
        upThread.join();
        chunkGeneratingThread.join();
    }
    else if(gs==EXIT)
    {
        fstream playerSave("save1player.txt",std::ofstream::out | std::ofstream::trunc);
        playerSave<<world->getPlayer().getPosition().x<<" "<<world->getPlayer().getPosition().y;
        playerSave.close();
        cerr<<"EXIT"<<endl;
        window->close();
    }
}

void Game::draw()
{
    //cout<<"CZYSZCZENIE"<<endl;
    window->clear();

    if(gs==INGAME||gs==ESCWINDOW)
    {
        world->spawnEntities();

        world->draw(*window);

        iface->draw(world->getPlayer(),*window);
        if(gs==ESCWINDOW)
        {
            menu->drawEscMenu(*window);
        }
    }
    else if(gs==MENU)
    {
        menu->draw(*window);
    }

    //cout<<"POKAZYWANIE"<<endl;
    window->display();
}
