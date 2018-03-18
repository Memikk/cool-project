#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED
#include "globals.h"

enum entityType{SHEEP,COW,PIG};
class Entity : public sf::Sprite
{
public:
    sf::Clock wanderClock;
    Entity(){changeTextureRect(0);};
    Entity(sf::Vector2f pos){setPosition(pos);desiredPos=pos;};
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
    Sheep(){};
    Sheep(sf::Vector2f pos):Entity(pos){};
};

#endif // ENTITIES_H_INCLUDED
