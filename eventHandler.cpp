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
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::LShift)
        {
            world.drink();
        }
        else if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Right&&world.getPlayer().eq.on)
        {
            world.dropItemOnGround(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
        }
        else if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left&&world.getPlayer().eq.on)
        {
            world.takeItem(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
            window->setMouseCursorVisible(false);
        }
        else if(event.type == sf::Event::MouseButtonReleased&&event.mouseButton.button==sf::Mouse::Left&&world.getPlayer().eq.on)
        {
            world.dropItemInEq(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
            window->setMouseCursorVisible(true);
        }
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::E)
        {
            world.getPlayer().eq.on=!world.getPlayer().eq.on;
        }
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::LControl)
        {
            world.mine();
        }
    }
}
