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
public:
    Block*** blocks;
    int ix,iy;
    int offsetX,offsetY;
    Chunk(int ix,int iy,siv::PerlinNoise& perlin,TextureLoader* tloader);
    void draw(sf::RenderWindow& window);
    bool operator==(const Chunk& chunk);
};

class World
{
    sf::RectangleShape daynight;
    float dayCounter=0;
    int adder=2;
    siv::PerlinNoise perlin;
    Player player;
    vector<Chunk> chunks;
    vector<Entity*> entities;
    TextureLoader* txtLoader;
public:
    int gameTime=18;
    World(TextureLoader* tloader);
    World(){};
    Player& getPlayer(){return player;};
    sf::Vector2i blockID(sf::Vector2f chunk,sf::Vector2f pos);
    void pickUpItem();
    bool exist(int x,int y) const;
    Block* blockCollision(sf::Vector2f pos);
    Chunk* getChunk(int x,int y);
    vector<Block*> getCollisions(sf::Vector2f pos);
    void spawnEntities();
    void generateChunks();
    void popChunks(int x,int y);
    void updateEntities(const sf::View& view);
    void updateChunks();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif // WORLD_H_INCLUDED
