#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include "globals.h"

enum entityType{SHEEP,COW,PIG};
class Entity : public sf::Sprite
{
public:
    int counter=0;
    bool wandering=false;
    Entity(){changeTextureRect(0);};
    Entity(sf::Vector2f pos){changeTextureRect(0);setPosition(pos);desiredPos=pos;};
    entityType type;
    sf::Vector2f vel,desiredPos;
    void wander();
    void moving(vector<Block*> collisions);
    void update(vector<Block*> collisions);
    void animate();
    void changeTextureRect(int value);
};

class Sheep : public Entity
{
public:
    Sheep():Entity(){};
    Sheep(sf::Vector2f pos):Entity(pos){};
};
class Cow : public Entity
{
public:
    Cow():Entity(){};
    Cow(sf::Vector2f pos):Entity(pos){};
};
class Pig : public Entity
{
public:
    Pig():Entity(){};
    Pig(sf::Vector2f pos):Entity(pos){};
};

#endif // ENTITIES_H_INCLUDED
