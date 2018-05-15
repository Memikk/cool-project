#include "eventHandler.h"

void EventHandler::checkEvents(World& world,sf::View& view,gameState& gs)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window->close();
        if(gs==INGAME)
        {
            if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Space)
            {
                if(world.getPlayer().eq.items.size()<20)
                    world.pickUpItem();
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
            else if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left&&!world.getPlayer().eq.on)
            {
                world.build(*window);
                world.mine(*window);
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

            if(event.type == sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::Num1||
                    event.key.code==sf::Keyboard::Num2||
                    event.key.code==sf::Keyboard::Num3||
                    event.key.code==sf::Keyboard::Num4||
                    event.key.code==sf::Keyboard::Num5))
            {
                world.getPlayer().eq.changeSlot(static_cast<unsigned>(event.key.code-27));
            }
        }
        else
        {
            if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                gs=INGAME;
                world.start(window,&view);
            }
        }
    }
}





















