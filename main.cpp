#include "game.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand( (unsigned) time(NULL) * getpid());
    sf::ContextSettings settings;
    //settings.antialiasingLevel=8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080),"",sf::Style::Fullscreen,settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Game game(window);

    while(window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}
