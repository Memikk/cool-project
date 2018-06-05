#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "eventHandler.h"
#include "world.h"
#include "globals.h"
#include "interface.h"
#include "saver.h"

class Menu
{
    sf::Texture* menuFrame;
    sf::Texture* escMenuTexture;
    sf::Texture* endScreenTexture;
    sf::Sprite frame;
    sf::Sprite escMenu;
    sf::Sprite endScreen;
    sf::RectangleShape background;
    public:
    Menu();
    sf::RectangleShape contBox,newBox,exitBox;
    void draw(sf::RenderWindow& window);
    void drawDead(sf::RenderWindow& window);
    void drawEscMenu(sf::RenderWindow& window);
};

class Game
{
    bool started=false;
    sf::RenderWindow* window;
    EventHandler* evHandler;
    TextureLoader* txtLoader;
    Interface* iface;
    Saver* saver;
    World* world;
    sf::View* view;
    Menu* menu;
    gameState gs=MENU;
public:
    Game(sf::RenderWindow& win);
    void update();
    void draw();

};

#endif // GAME_H_INCLUDED
