#include "block.h"

Block::Block()
{
    setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    setFillColor(sf::Color::Transparent);
}
Block::Block(const Block& b)
{
    collision=b.collision;
    base=b.base;
}
Block::Block(sf::Vector2f pos)
{
    setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    setPosition(pos);
    setFillColor(sf::Color::Transparent);
}

Grass::Grass():Block()
{
    setFillColor(sf::Color::White);
    type=GRASS;
}
Grass::Grass(const Grass& g):Block(g)
{
    object=g.object;
}

void Water::animate()
{
    if(animationClock.getElapsedTime().asMilliseconds()>500)
    {
        nextFrame();
    }
}

void Water::nextFrame()
{
    sf::IntRect tRect(BLOCK_SIZE*frame,BLOCK_SIZE*column,BLOCK_SIZE,BLOCK_SIZE);
    frame++;
    if(frame>4) frame=0;
    setTextureRect(tRect);
}

Sand::Sand():Block()
{
    type=SAND;
    setFillColor(sf::Color::White);
}

Dirt::Dirt():Block()
{
    type=DIRT;
    setFillColor(sf::Color::White);
}

