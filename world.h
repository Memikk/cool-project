#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "block.h"
#include "player.h"
#include "interface.h"
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
    Block& randBlock(bool collision=false);
    void draw(sf::RenderWindow& window);
    bool operator==(const Chunk& chunk);
};

class World
{
    sf::RectangleShape daynight;
    float dayCounter=0;
    float redCounter=0;
    int adder=2;
    siv::PerlinNoise perlin;
    Player player;
    vector<Chunk> chunks;
    vector<Entity*> entities;
    TextureLoader* txtLoader;
    Interface* iface;
public:
    int gameTime=18;
    int days=0;
    World(TextureLoader* tloader,Interface* intface);
    World(){};
    Player& getPlayer(){return player;};
    sf::Vector2i blockID(sf::Vector2f chunk,sf::Vector2f pos);
    void pickUpItem();
    void dropItem(sf::Vector2f mpos);
    void eat(sf::Vector2f mpos);
    void drink();
    bool exist(int x,int y) const;
    Block* blockCollision(sf::Vector2f pos);
    Block* getBlock(sf::Vector2f pos);
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
