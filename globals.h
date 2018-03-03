#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <SFML/Graphics.hpp>

extern sf::Clock animationClock;
extern unsigned BLOCK_SIZE;
extern unsigned CHUNK_SIZE;
sf::Vector2f center(sf::RectangleShape);
sf::Vector2f center(sf::Sprite);

#endif // GLOBALS_H_INCLUDED
