#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "eventHandler.h"
#include "world.h"
#include "globals.h"
#include "interface.h"

enum gameState{MENU,INGAME};

class Game
{
    sf::RenderWindow* window;
    EventHandler* evHandler;
    TextureLoader* txtLoader;
    Interface* iface;
    World* world;
    sf::View* view;
public:
    Game(sf::RenderWindow& win);
    void update();
    void draw();
};

#endif // GAME_H_INCLUDED
