#include "player.h"

Player::Player()
{
    vel=sf::Vector2f();
    acc=sf::Vector2f(0.05,0.05);
    background.setPosition(getPosition());
    background.setSize(sf::Vector2f(1920,1080));
    background.setFillColor(sf::Color(0,72,0));
    changeTextureRect(0);
    hpBar.setScale(3,3);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Player::update(vector<Block*>& collisions)
{
    //cout<<"PLAYER UPDATE"<<endl;
    moving(collisions);
    //cout<<"PO RUCHU GRACZA"<<endl;
    animate(collisions);
    //cout<<"PO ANIMACJI GRACZA"<<endl;
}

void Player::moving(vector<Block*>& collisions)
{
    bool movingX=true;
    bool movingY=true;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        changeTextureRect(0);
        vel.y=speed;
        dir=DOWN;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        changeTextureRect(2);
        vel.y=-speed;
        dir=UP;
    }
    else
    {
        if(vel.y<0.1&&vel.y>-0.1)
            vel.y=0;
        else if(vel.y)
            vel.y*=0.85;
        if(movingY)
            movingY=false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        changeTextureRect(1);
        vel.x=-speed;
        dir=LEFT;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        changeTextureRect(3);
        vel.x=speed;
        dir=RIGHT;
    }
    else
    {
        if(vel.x<0.1&&vel.x>-0.1)
            vel.x=0;
        else if(vel.x)
            vel.x*=0.85;
        if(movingX)
            movingX=false;
    }

    for(auto& c:collisions)
    {
        sf::Sprite temp1=*this;
        sf::Sprite temp2=*this;

        temp1.move(vel.x,0);
        if(c->collision&&temp1.getGlobalBounds().intersects(c->getGlobalBounds())) vel.x=0;
        temp2.move(0,vel.y);
        if(c->collision&&temp2.getGlobalBounds().intersects(c->getGlobalBounds())) vel.y=0;
    }

    if(movingX&&movingY)
    {
        vel.x=vel.x/2*sqrt(2);
        vel.y=vel.y/2*sqrt(2);
    }
}

void Player::changeTextureRect(int value)
{
    sf::IntRect t(0,BLOCK_SIZE*value,BLOCK_SIZE,BLOCK_SIZE);
    setTextureRect(t);
}

void Player::animate(vector<Block*>& collisions)
{
    move(vel);
    background.setPosition(getPosition()-background.getSize()/2.f);
}
