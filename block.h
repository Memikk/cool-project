#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"

class Block : public sf::RectangleShape
{
public:
    bool base=true;
    Block();
    Block(sf::Vector2f pos);
};

class Water : public Block
{
public:
    Water();
};

class Sand : public Block
{
public:
    Sand();
};

class Stone : public Block
{
public:
    Stone();
};


#endif // BLOCK_H_INCLUDED
