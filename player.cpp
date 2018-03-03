#include "player.h"

Player::Player()
{
    desiredPos=getPosition();
    background.setPosition(getPosition());
    background.setSize(sf::Vector2f(1920,1080));
    background.setFillColor(sf::Color(40,120,10));
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Player::update(vector<bool> collisions)
{
    //cout<<"PLAYER UPDATE"<<endl;
    moving(collisions);
    //cout<<"PO RUCHU GRACZA"<<endl;
    animate();
    //cout<<"PO ANIMACJI GRACZA"<<endl;
}

void Player::moving(vector<bool> collisions)
{
    if(!animating)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(!collisions[5])
            {
                desiredPos.y+=BLOCK_SIZE;
                animating=true;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(!collisions[1])
            {
                desiredPos.y-=BLOCK_SIZE;
                animating=true;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(!collisions[7])
            {
                desiredPos.x-=BLOCK_SIZE;
                animating=true;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!collisions[3])
            {
                desiredPos.x+=BLOCK_SIZE;
                animating=true;
            }
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
