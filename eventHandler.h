#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

struct EventHandler
{
    EventHandler(){};
    sf::Event event;
    void checkEvents(sf::RenderWindow& window)
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed||
              (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
    }
};

#endif // EVENTHANDLER_H_INCLUDED
