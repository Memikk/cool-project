#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "block.h"
#include <sstream>
#include "player.h"
#include "interface.h"
#include <vector>
#include <iostream>
#include "perlinNoise.hpp"
#include "textureLoader.h"
#include "saver.h"

using namespace std;

class Chunk
{
public:
    Block*** blocks;
    int ix,iy;
    int offsetX,offsetY;
    Chunk(int ix,int iy,siv::PerlinNoise& perlin,TextureLoader* tloader);
    Chunk(){};
    sf::Vector2i getXY(){return sf::Vector2i(ix,iy);};
    Block& randBlock(bool collision=false);
    void draw(sf::RenderWindow& window);
    bool operator==(const Chunk& chunk);
};

class World
{
    Saver* saver;
    sf::Texture daynightTexture;
    sf::Sprite daynight;
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
    int gameTime=8;
    int days=1;
    World(TextureLoader* tloader,Interface* intface,Saver* s);
    World(){};
    Player& getPlayer(){return player;};
    sf::Vector2i blockID(sf::Vector2f chunk,sf::Vector2f pos);
    void pickUpItem();
    void dropItemOnGround(sf::Vector2f mpos);
    void takeItem(sf::Vector2f mpos);
    void dropItemInEq(sf::Vector2f mpos);
    void eat();
    void drink();
    void mine(sf::RenderWindow& window);
    void attack(sf::RenderWindow& window);
    void build(sf::RenderWindow& window);
    void harvest(sf::RenderWindow& window);
    void lightup(sf::RenderWindow& window);
    bool exist(int x,int y) const;
    Block* blockCollision(sf::Vector2f pos);
    Block* getBlock(sf::Vector2f pos);
    Chunk& getChunkFromPos(sf::Vector2f pos);
    Chunk* getChunk(int x,int y);
    vector<Block*> getCollisions(sf::Vector2f pos);
    void spawnEntities();
    void generateChunks();
    void loadChunks();
    void popChunks(int x,int y);
    void updateEntities(const sf::View& view);
    void updateChunks();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void start(sf::RenderWindow* window,sf::View* view);
    void newStart(sf::RenderWindow* window,sf::View* view);
    void save(Chunk& chunk,sf::Vector2i id);
};

#endif // WORLD_H_INCLUDED
