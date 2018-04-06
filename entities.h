#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include "globals.h"

enum entityType{SHEEP,COW,PIG,WOLF};
class Entity : public sf::Sprite
{
public:
    int counter=0;
    bool wandering=false;
    Entity(entityType t):type(t){changeTextureRect(0);};
    Entity(sf::Vector2f pos,entityType t):type(t){changeTextureRect(0);setPosition(pos);desiredPos=pos;};
    entityType type;
    sf::Vector2f vel,desiredPos;
    void wander();
    void moving(vector<Block*> collisions);
    virtual void update(vector<Block*> collisions);
    void animate();
    void changeTextureRect(int value);
};

class Sheep : public Entity
{
public:
    Sheep():Entity(SHEEP){};
    Sheep(sf::Vector2f pos):Entity(pos,SHEEP){};
};
class Cow : public Entity
{
public:
    Cow():Entity(COW){};
    Cow(sf::Vector2f pos):Entity(pos,COW){};
};
class Pig : public Entity
{
public:
    Pig():Entity(PIG){};
    Pig(sf::Vector2f pos):Entity(pos,PIG){};
};
class Wolf : public Entity
{
public:
    void hunt(vector<Entity*>& entities);
    void update(vector<Block*> collisions,vector<Entity*>& entities);
    Wolf():Entity(WOLF){};
    Wolf(sf::Vector2f pos):Entity(pos,WOLF){};
};

#endif // ENTITIES_H_INCLUDED
