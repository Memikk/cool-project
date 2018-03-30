#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED
#include "globals.h"
#include "world.h"

struct EventHandler
{
    EventHandler(sf::RenderWindow& w):window(&w) {};
    sf::Event event;
    sf::RenderWindow* window;
    void checkEvents(World& world,sf::View& view);
};


#endif // EVENTHANDLER_H_INCLUDED
