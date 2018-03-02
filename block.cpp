#include "block.h"

Block::Block()
{
    setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    setFillColor(sf::Color::Green);
    setOutlineColor(sf::Color::Black);
    //setOutlineThickness(1);
}
Block::Block(sf::Vector2f pos)
{
    setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    setPosition(pos);
    setFillColor(sf::Color::Green);
    setOutlineColor(sf::Color::Black);
    //setOutlineThickness(1);
}

Water::Water():Block()
{
    setFillColor(sf::Color(0,0,120));
    base=false;
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
