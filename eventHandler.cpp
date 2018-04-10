#include "eventHandler.h"

void EventHandler::checkEvents(World& world,sf::View& view)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window->close();
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Space)
        {
            if(world.getPlayer().eq.items.size()<20) world.pickUpItem();
        }
        else if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Right&&world.getPlayer().eq.on)
        {
            world.dropItem(window->mapPixelToCoords(sf::Mouse::getPosition()));
        }
        else if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left&&world.getPlayer().eq.on)
        {
            world.eat(window->mapPixelToCoords(sf::Mouse::getPosition()));
        }
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::E)
        {
            world.getPlayer().eq.on=!world.getPlayer().eq.on;
        }
    }
}
