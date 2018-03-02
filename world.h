#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "block.h"
#include "player.h"
#include <vector>
#include <iostream>
#include "perlinNoise.hpp"
#include "textureLoader.h"
using namespace std;

class Chunk
{
    Block*** blocks;
public:
    int ix,iy;
    int offsetX,offsetY;
    Chunk(int ix,int iy,siv::PerlinNoise& perlin,TextureLoader* tloader);
    void draw(sf::RenderWindow& window);
    bool operator==(const Chunk& chunk);
};

class World
{
    siv::PerlinNoise perlin;
    Player player;
    vector<Chunk> chunks;
    TextureLoader* txtLoader;
public:
    World(TextureLoader* tloader);
    Player& getPlayer(){return player;};
    bool exist(int x,int y);
    void generateChunks();
    void update();
    void draw(sf::RenderWindow& window);
    void setTextures();
};

#endif // WORLD_H_INCLUDED
