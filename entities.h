#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include "globals.h"

enum entityType{SHEEP,COW,PIG};
class Entity : public sf::Sprite
{
public:
    int counter=0;
    int id;
    bool wandering=false;
    Entity(int id):id(id){changeTextureRect(0);};
    Entity(sf::Vector2f pos,int id):id(id){changeTextureRect(0);setPosition(pos);desiredPos=pos;};
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
    Sheep(int id):Entity(id){};
    Sheep(sf::Vector2f pos,int id):Entity(pos,id){};
};

#endif // ENTITIES_H_INCLUDED
