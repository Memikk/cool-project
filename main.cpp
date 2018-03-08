#include "game.h"
#include <time.h>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080),"",sf::Style::Default);
    window.setFramerateLimit(60);

    Game game(window);

    while(window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}
