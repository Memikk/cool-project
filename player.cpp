#include "player.h"

Player::Player()
{
    vel=sf::Vector2f();
    acc=sf::Vector2f(0.05,0.05);
    background.setPosition(getPosition());
    background.setSize(sf::Vector2f(1920,1080));
    background.setFillColor(sf::Color(40,120,10));
    hitbox=sf::FloatRect(getPosition().x/3,getPosition().y*2/3,vh::getSize(*this).x/3,vh::getSize(*this).y*2/3);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Player::update(vector<Block*>& collisions)
{
    //cout<<"PLAYER UPDATE"<<endl;
    moving();
    //cout<<"PO RUCHU GRACZA"<<endl;
    animate(collisions);
    //cout<<"PO ANIMACJI GRACZA"<<endl;
}

void Player::moving()
{
    bool movingX=true;
    bool movingY=true;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        vel.y=speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        vel.y=-speed;
    }
    else
    {
        if(vel.y) vel.y*=0.8;
        if(movingY) movingY=false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        vel.x=-speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        vel.x=speed;
    }
    else
    {
        if(vel.x) vel.x*=0.8;
        if(movingX) movingX=false;
    }

    if(movingX&&movingY)
    {
        vel.x=vel.x/2*sqrt(2);
        vel.y=vel.y/2*sqrt(2);
    }
}

void Player::animate(vector<Block*>& collisions)
{
    sf::RectangleShape temp;
    temp.setPosition(getPosition()+vel);

    bool dontMove=false;
    for(auto& c:collisions)
    {
        if(c->getGlobalBounds().intersects(temp.getGlobalBounds()))
        {
            dontMove=true;
            break;
        }
    }
    if(!dontMove) move(vel);
    background.setPosition(getPosition()-background.getSize()/2.f);
//    if(desiredPos!=getPosition())
//    {
//        int x=(desiredPos.x==getPosition().x)?0:(desiredPos.x<getPosition().x)?-5:5;
//        int y=(desiredPos.y==getPosition().y)?0:(desiredPos.y<getPosition().y)?-5:5;
//        move(x,y);
//    }
//    else
//    {
//        animating=false;
//        background.setPosition(getPosition()-background.getSize()/2.f);
//    }
}
