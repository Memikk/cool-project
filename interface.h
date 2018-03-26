#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "globals.h"
#include "player.h"

class FPS
{
public:
    FPS();
    sf::Text fps;
    sf::Font font;
    float mFrame;
    int mFps;
    void countFPS();
    void update();
};
class Interface
{
public:
    FPS fps;
    Interface() {};
    void update();
    void draw(Player& p,sf::RenderWindow& window);
};

#endif // INTERFACE_H_INCLUDED
