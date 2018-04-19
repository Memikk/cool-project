#include "game.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand( (unsigned) time(NULL) * getpid());
    sf::ContextSettings settings;
    //settings.antialiasingLevel=8;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop,"",sf::Style::Fullscreen,settings);
    //window.setMouseCursorVisible(false);
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
