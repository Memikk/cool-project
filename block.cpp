#include "block.h"

Block::Block()
{
    setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    setFillColor(sf::Color::Transparent);
}
Block::Block(sf::Vector2f pos)
{
    setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    setPosition(pos);
    setFillColor(sf::Color::Transparent);
}

Grass::Grass():Block()
{
}

Water::Water():Block()
{
    animationClock.restart();
    setFillColor(sf::Color::White);
    base=false;
}

void Water::animate()
{
    if(animationClock.getElapsedTime().asSeconds()>0.5)
    {
        nextFrame();
        animationClock.restart();
    }
}

void Water::nextFrame()
{
    sf::IntRect tRect(0,10*frame,10,10);
    frame++;
    if(frame>4) frame=0;
    setTextureRect(tRect);
}

Sand::Sand():Block()
{
    setFillColor(sf::Color(200,200,60));
    base=false;
}

Stone::Stone():Block()
{
    setFillColor(sf::Color(51,51,51));
    base=false;
}
