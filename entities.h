#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include "globals.h"
#include "textureLoader.h"

enum entityType{SHEEP,COW,PIG,WOLF};
class Entity : public sf::Sprite
{
public:
    entityType type;
    TextureLoader* txtLoader;
    Block* block;
    int counter=0;
    bool wandering=false;
    sf::Vector2f vel,desiredPos;

    Entity(TextureLoader* tloader,entityType t):type(t),txtLoader(tloader){changeTextureRect(0);};
    Entity(TextureLoader* tloader,sf::Vector2f pos,entityType t):type(t),txtLoader(tloader){changeTextureRect(0);setPosition(pos);desiredPos=pos;};

    void wander();
    void moving(vector<Block*> collisions);
    virtual void update(vector<Block*> collisions);
    void animate();
    void changeTextureRect(int value);
};

class Sheep : public Entity
{
public:
    Sheep(TextureLoader* tloader):Entity(tloader,SHEEP){};
    Sheep(TextureLoader* tloader,sf::Vector2f pos):Entity(tloader,pos,SHEEP){};
};
class Cow : public Entity
{
public:
    Cow(TextureLoader* tloader):Entity(tloader,COW){};
    Cow(TextureLoader* tloader,sf::Vector2f pos):Entity(tloader,pos,COW){};
};
class Pig : public Entity
{
public:
    Pig(TextureLoader* tloader):Entity(tloader,PIG){};
    Pig(TextureLoader* tloader,sf::Vector2f pos):Entity(tloader,pos,PIG){};
};
class Wolf : public Entity
{
public:
    void hunt(vector<Entity*>& entities);
    void update(vector<Block*> collisions,vector<Entity*>& entities);
    Wolf(TextureLoader* tloader):Entity(tloader,WOLF){};
    Wolf(TextureLoader* tloader,sf::Vector2f pos):Entity(tloader,pos,WOLF){};
};

#endif // ENTITIES_H_INCLUDED
