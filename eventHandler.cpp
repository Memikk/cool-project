#include "eventHandler.h"

void EventHandler::checkEvents(World& world,sf::View& view,gameState& gs,vector<sf::RectangleShape> boxes)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            if(gs==ESCWINDOW) gs=INGAME;
            else gs=ESCWINDOW;
        }
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
            else if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Right)
            {
                if(world.getPlayer().eq.on)
                {
                    world.dropItemOnGround(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
                }
                world.eat();
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
                world.harvest(*window);
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
        else if(gs==ESCWINDOW)
        {
            if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                if(boxes[0].getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
                {
                    gs=INGAME;
                }
                else if(boxes[1].getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
                {
                    gs=EXIT;
                }
            }
        }
        else
        {
            if(event.type == sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                if(boxes[0].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition()))
                {
                    gs=INGAME;
                    world.start(window,&view);
                }
                else if(boxes[1].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition()))
                {
                    gs=INGAME;
                    world.newStart(window,&view);
                }
                else if(boxes[2].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition()))
                {
                    gs=EXIT;
                }
            }
        }
    }
}





















