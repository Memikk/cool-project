#include "globals.h"

unsigned BLOCK_SIZE=50;
unsigned CHUNK_SIZE=16;
sf::Clock animationClock;
siv::PerlinNoise worldGenNoise;
siv::PerlinNoise objectNoise;

sf::Vector2f center(sf::RectangleShape r)
{
    return sf::Vector2f(r.getPosition().x+r.getSize().x/2,
                        r.getPosition().y+r.getSize().y/2);
}
sf::Vector2f center(sf::Sprite s)
{
    return sf::Vector2f(s.getGlobalBounds().left+s.getGlobalBounds().width/2,
                        s.getGlobalBounds().top+s.getGlobalBounds().height/2);
}
