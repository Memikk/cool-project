#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "eventHandler.h"
#include "world.h"
#include "globals.h"

enum gameState{MENU,INGAME};

class Game
{
    sf::Text fps;
    sf::Font font;
    float mFrame;
    int mFps;
    void countFPS();

    sf::RenderWindow* window;
    EventHandler evHandler;
    TextureLoader* txtLoader;
    World* world;
    sf::View view;
public:
    Game(sf::RenderWindow& win);
    void update();
    void draw();
};

#endif // GAME_H_INCLUDED
