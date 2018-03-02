#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"

class Block : public sf::RectangleShape
{
public:
    bool base=true;
    Block();
    Block(sf::Vector2f pos);
    virtual void animate()=0;
};

class Grass : public Block
{
public:
    Grass();
    void animate(){};
};

class Water : public Block
{
    int frame=0;
    sf::Clock animationClock;
public:
    Water();
    void animate();
    void nextFrame();
};

class Sand : public Block
{
public:
    Sand();
    void animate(){};
};

class Stone : public Block
{
public:
    Stone();
    void animate(){};
};


#endif // BLOCK_H_INCLUDED
