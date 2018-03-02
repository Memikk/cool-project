#include "player.h"

Player::Player()
{
    desiredPos=getPosition();
    background.setPosition(getPosition());
    background.setSize(sf::Vector2f(1920,1080));
    background.setFillColor(sf::Color(0,120,0));
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Player::update()
{
    moving();
    animate();
}

void Player::moving()
{
    if(!animating)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            desiredPos.y+=BLOCK_SIZE;
            animating=true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            desiredPos.y-=BLOCK_SIZE;
            animating=true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            desiredPos.x-=BLOCK_SIZE;
            animating=true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            desiredPos.x+=BLOCK_SIZE;
            animating=true;
        }
    }
}

void Player::animate()
{
    if(desiredPos!=getPosition())
    {
        int x=(desiredPos.x==getPosition().x)?0:(desiredPos.x<getPosition().x)?-5:5;
        int y=(desiredPos.y==getPosition().y)?0:(desiredPos.y<getPosition().y)?-5:5;
        move(x,y);
    }
    else
    {
        animating=false;
        background.setPosition(getPosition()-background.getSize()/2.f);
    }
}
