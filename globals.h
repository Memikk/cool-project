#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "perlinNoise.hpp"

enum blockType{GRASS,SAND,STONE,WATER};
extern siv::PerlinNoise worldGenNoise;
extern siv::PerlinNoise objectNoise;
extern sf::Clock animationClock;
extern unsigned BLOCK_SIZE;
extern unsigned CHUNK_SIZE;
sf::Vector2f center(sf::RectangleShape);
sf::Vector2f center(sf::Sprite);

#endif // GLOBALS_H_INCLUDED
