#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include "globals.h"

enum entityType{SHEEP,COW,PIG};
class Entity : public sf::Sprite
{
public:
    int id;
    bool wandering=false;
    sf::Clock wanderClock;
    Entity(int id):id(id){changeTextureRect(0);};
    Entity(sf::Vector2f pos,int id):id(id){setPosition(pos);desiredPos=pos;};
    entityType type;
    sf::Vector2f vel,desiredPos;
    void wander();
    void moving();
    void update();
    void animate();
    void changeTextureRect(int value);
};

class Sheep : public Entity
{
public:
    Sheep(int id):Entity(id){};
    Sheep(sf::Vector2f pos,int id):Entity(pos,id){};
};

#endif // ENTITIES_H_INCLUDED
