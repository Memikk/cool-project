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

void Block::draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

Grass::Grass(bool tree,bool plant):Block(),tree(tree),plant(plant)
{
    object.setScale(5,5);
    if(tree) collision=true;
}
Grass::Grass(const Grass& g):Block(g)
{
    object=g.object;
}

void Grass::setObjectTexture(sf::Texture& t)
{
    object.setTexture(t);
}

void Grass::initialize()
{
    object.setPosition(getPosition());
}

void Grass::draw(sf::RenderWindow& window)
{
    window.draw(object);
}

Water::Water():Block()
{
    setFillColor(sf::Color::White);
    base=false;
    collision=true;
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
    setFillColor(sf::Color::White);
    base=false;
    collision=true;
}
