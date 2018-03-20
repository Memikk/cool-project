#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED
#include "globals.h"

struct EventHandler
{
    EventHandler(sf::RenderWindow& w):window(&w){};
    sf::Event event;
    sf::RenderWindow* window;
    void checkEvents(sf::View& view)
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
                    if(view.getSize().x>400) zoom=-5;
                    else zoom=0;
                }
                else if(event.mouseWheelScroll.delta<0)
                {
                    if(view.getSize().x<1500) zoom=5;
                    else zoom=0;
                }
                else zoom=0;
                view.setSize(view.getSize()+sf::Vector2f(zoom*16,zoom*9));
                cout<<view.getSize().x<<" "<<view.getSize().y<<endl;
                window->setView(view);
            }
        }
    }
};

#endif // EVENTHANDLER_H_INCLUDED
