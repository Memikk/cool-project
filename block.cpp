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
    setFillColor(sf::Color::White);

    if(tree)
    {
        object.setScale(1,1);
        collision=true;
    }
    else
    {
        object.setScale(2.5,2.5);
    }
}
Grass::Grass(const Grass& g):Block(g)
{
    object=g.object;
}

void Grass::setObjectTexture(sf::Texture& t,int offset)
{
    sf::IntRect r;
    if(plant) r=sf::IntRect(0,20*offset,20,20);
    else r=sf::IntRect(0,BLOCK_SIZE*offset,BLOCK_SIZE,BLOCK_SIZE);
    object.setTextureRect(r);
    object.setTexture(t);
}

void Grass::initialize()
{
    object.setPosition(getPosition());
}

void Grass::draw(sf::RenderWindow& window)
{
    window.draw(*this);
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
    sf::IntRect tRect(BLOCK_SIZE*frame,BLOCK_SIZE*type,BLOCK_SIZE,BLOCK_SIZE);
    frame++;
    if(frame>4) frame=0;
    setTextureRect(tRect);


}

Sand::Sand():Block()
{
    setFillColor(sf::Color::White);
    base=false;
}

Stone::Stone():Block()
{
    setFillColor(sf::Color::White);
    base=false;
    collision=true;
}
