#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "eventHandler.h"
#include "world.h"
#include "textureLoader.h"

enum gameState{MENU,INGAME};

class Game
{
    sf::Text fps;
    sf::Font font;
    float mFrame;
    int mFps;

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
