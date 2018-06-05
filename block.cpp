#include "block.h"

void Object::shake()
{
    while(shakePos.size()) shakePos.pop();
    shakePos.push(getPosition());
    startPosition=getPosition();
    comeback=startPosition;
    for(int i=0;i<4;i++)
    {
        shakePos.push(getPosition()+sf::Vector2f(rand()%4-2,rand()%4-2));
    }
}

void Object::update()
{
    if(shakePos.size())
    {
        float vx=(shakePos.front().x-startPosition.x)/2;
        float vy=(shakePos.front().y-startPosition.y)/2;
        if(vh::distance(getPosition(),shakePos.front())>0.01)
        //if(getPosition()!=shakePos.front())
        {
            move(vx,vy);
        }
        else
        {
            setPosition(shakePos.front());
            startPosition=shakePos.front();
            shakePos.pop();
        }
        if(!shakePos.size())
        {
            setPosition(comeback);
        }
    }
}

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
}

void Water::animate()
{
    counter++;
    if(counter==35)
    {
        counter=0;
        nextFrame();
    }
}
void AnimatedPlant::animate()
{
    counter++;
    if(counter==30)
    {
        counter=0;
        nextFrame();
    }
}

void Water::nextFrame()
{
    sf::IntRect tRect(BLOCK_SIZE*frame,BLOCK_SIZE*column,BLOCK_SIZE,BLOCK_SIZE);
    frame++;
    if(frame>4)
        frame=0;
    setTextureRect(tRect);
}
void AnimatedPlant::nextFrame()
{
    sf::IntRect tRect(BLOCK_SIZE*frame,BLOCK_SIZE*column,BLOCK_SIZE,BLOCK_SIZE);
    frame++;
    if(frame>3)
        frame=0;
    setTextureRect(tRect);
}

void Block::draw(sf::RenderWindow& window)
{
    if(grass!=nullptr)
    {
        if(grass->side)
        {
            if(object!=nullptr&&object->getType()==objectType::WATER)
            {
                window.draw(*object);
            }
            else
            {
                window.draw(*this);
            }
        }
        if(cover!=nullptr&&cover->side)
            window.draw(*grass);
        else if(cover==nullptr)
            window.draw(*grass);
        grass->setColor(sf::Color::White);
    }
    else
        window.draw(*this);
    if(cover!=nullptr)
    {
        window.draw(*cover);
        cover->setColor(sf::Color::White);
    }
    if(object==nullptr&&decoration)
    {
        window.draw(*decoration);
    }
    if(object!=nullptr)
    {
        if((object->getType()==objectType::WATER&&grass==nullptr)||object->getType()!=objectType::WATER)
        {
            window.draw(*object);
        }

    }
    else
    {
        for(int i=items.size()-1;i>=0;i--)
        {
            items[i]->draw(window);
        }
    }
};

Dirt::Dirt():Block()
{
    type=DIRT;
    setFillColor(sf::Color::White);
}

