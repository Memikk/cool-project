#include "entities.h"

void Entity::wander()
{
    int x=rand()%200*((rand()%2==0)?-1:1);
    int y=rand()%200*((rand()%2==0)?-1:1);

    desiredPos.x=x+getPosition().x;
    desiredPos.y=y+getPosition().y;
}

void Entity::moving()
{
    vel.x=(desiredPos.x>getPosition().x)?1:-1;
    vel.y=(desiredPos.y>getPosition().y)?1:-1;

    if(abs(desiredPos.x-getPosition().x)<2)
    {
        vel.x=0;
    }
    if(abs(desiredPos.y-getPosition().y)<2)
    {
        vel.y=0;
    }

//    for(auto& c:collisions)
//    {
//        sf::Sprite temp1=*this;
//        sf::Sprite temp2=*this;
//
//        temp1.move(vel.x,0);
//        if(c->collision&&temp1.getGlobalBounds().intersects(c->getGlobalBounds())) vel.x=0;
//        temp2.move(0,vel.y);
//        if(c->collision&&temp2.getGlobalBounds().intersects(c->getGlobalBounds())) vel.y=0;
//    }

    move(vel);
}

void Entity::update()
{
    if(wanderClock.getElapsedTime().asSeconds()>5.0)
    {
        wanderClock.restart();
        wander();
    }
    moving();
}
