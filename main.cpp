#include "game.h"
#include <time.h>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    sf::ContextSettings settings;
    //settings.antialiasingLevel=8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080),"",sf::Style::Default,settings);
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
