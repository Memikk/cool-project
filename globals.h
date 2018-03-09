#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "perlinNoise.hpp"
#include "block.h"

class Block;
enum blockType{GRASS,SAND,STONE,WATER};
extern siv::PerlinNoise worldGenNoise;
extern siv::PerlinNoise objectNoise;
extern sf::Clock animationClock;
extern int speed;
extern int BLOCK_SIZE;
extern int CHUNK_SIZE;

namespace vh
{
sf::Vector2f center(const sf::RectangleShape&);
sf::Vector2f center(const sf::Sprite&);
sf::Vector2f center(const Block& b);
sf::Vector2f getSize(const sf::Sprite&);
}

#endif // GLOBALS_H_INCLUDED
