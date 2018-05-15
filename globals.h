#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "block.h"
#include "perlinNoise.hpp"
#include "thread.h"
#include "equipment.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Block;
class TextureLoader;
class Player;
class Chunk;
class World;
class PopUp;
//class Interface;
enum gameState{MENU,INGAME};
enum direction{UP,RIGHT,DOWN,LEFT};
extern siv::PerlinNoise worldGenNoise;
extern siv::PerlinNoise objectNoise;
extern siv::PerlinNoise objectNoise2;
extern sf::Clock animationClock;
extern sf::Clock fpsClock;
extern sf::Clock spawningClock;
extern sf::Clock dayClock;
extern float speed;
extern float zoom;
extern int BLOCK_SIZE;
extern int CHUNK_SIZE;

extern string to_string(int value);

namespace vh
{
template<typename T>
T& randElement(vector<T>& v)
{
    return v[rand()%v.size()];
}
sf::Vector2f center(const sf::RectangleShape&);
sf::Vector2f center(const sf::Sprite&);
sf::Vector2f center(const Block& b);
sf::Vector2f getSize(const sf::Sprite&);
sf::Vector2f randomPos(int radius,const sf::Sprite& s);
float distance(sf::Vector2f,sf::Vector2f);
float distance(float,float,float,float);
}
#endif // GLOBALS_H_INCLUDED

