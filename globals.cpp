#include "globals.h"

int BLOCK_SIZE=50;
int CHUNK_SIZE=16;
float speed=3.5;
sf::Clock animationClock;
sf::Clock fpsClock;
sf::Clock spawningClock;
siv::PerlinNoise worldGenNoise;
siv::PerlinNoise objectNoise;
siv::PerlinNoise dirtNoise;

sf::Vector2f vh::center(const sf::RectangleShape& r)
{
    return sf::Vector2f(r.getPosition().x+r.getSize().x/2,
                        r.getPosition().y+r.getSize().y/2);
}
sf::Vector2f vh::center(const sf::Sprite& s)
{
    return sf::Vector2f(s.getGlobalBounds().left+s.getGlobalBounds().width/2,
                        s.getGlobalBounds().top+s.getGlobalBounds().height/2);
}
sf::Vector2f vh::center(const Block& b)
{
    return sf::Vector2f(b.getPosition().x+b.getSize().x/2,
                        b.getPosition().y+b.getSize().y/2);
}
sf::Vector2f vh::getSize(const sf::Sprite& s)
{
    return sf::Vector2f(s.getGlobalBounds().left+s.getGlobalBounds().width,
                        s.getGlobalBounds().top+s.getGlobalBounds().height);
}
sf::Vector2f vh::randomPos(int radius,const sf::Sprite& s)
{
    return sf::Vector2f(s.getPosition().x+(rand()%radius)*((rand()%2)?-1:1),
                        s.getPosition().y+(rand()%radius)*((rand()%2)?-1:1));
}
