#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "globals.h"
#include "textureLoader.h"
#include "player.h"

class PopUp : public sf::Sprite
{
public:
    float counter=255;
    sf::Vector2f desiredPos;
    sf::Sprite item;
    sf::Vector2f base;
    int offset=0;
    int offset2=0;
    PopUp(sf::Texture* t);
    void update();
};

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
    sf::Sprite cursor;
    sf::Font font;
    sf::Text gTime;
    TextureLoader* txtLoader;
    vector<PopUp> popUps;
    FPS fps;
    Interface(TextureLoader* tLoader);
    void popUp(int id);
    void setTime(int t);
    void update(Player& p,sf::RenderWindow& window);
    void draw(Player& p,sf::RenderWindow& window);
};

#endif // INTERFACE_H_INCLUDED
