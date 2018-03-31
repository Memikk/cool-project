#include "eventHandler.h"

void EventHandler::checkEvents(World& world,sf::View& view)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window->close();
        else if(event.type == sf::Event::MouseWheelScrolled)
        {
            cout<<event.mouseWheelScroll.delta<<endl;
            if(event.mouseWheelScroll.delta>0)
            {
                if(view.getSize().x>400)
                    zoom=-5;
                else
                    zoom=0;
            }
            else if(event.mouseWheelScroll.delta<0)
            {
                if(view.getSize().x<1500)
                    zoom=5;
                else
                    zoom=0;
            }
            else
                zoom=0;
            view.setSize(view.getSize()+sf::Vector2f(zoom*16,zoom*9));
            window->setView(view);
        }
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Space)
        {
            world.pickUpItem();
        }
        else if(event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::E)
        {
            world.getPlayer().eq.on=!world.getPlayer().eq.on;
        }
    }
}
