#include "entities.h"

void Entity::wander()
{
    int x=(rand()*id)%200;
    x*=((rand()%2==0)?-1:1);
    int y=(rand()*id)%200;
    y*=((rand()%2==0)?-1:1);
    cout<<x<<" "<<y<<endl;

    desiredPos.x=x+getPosition().x;
    desiredPos.y=y+getPosition().y;
}

void Entity::moving()
{
    float offsetY = (sin(vh::distance(desiredPos,getPosition())*16*M_PI/180));
    if(abs(desiredPos.x-getPosition().x)<2)
    {
        vel.x=0;
    }
    else vel.x=(desiredPos.x>getPosition().x)?1:-1;
    if(abs(desiredPos.y-getPosition().y)<2)
    {
        vel.y=0;
    }
    else vel.y=(desiredPos.y>getPosition().y)?1:-1;

    if(vel.y<0)
    {
        if(vel.x<0) changeTextureRect(1);
        else if(vel.x>0) changeTextureRect(3);
        else changeTextureRect(2);
    }
    else
    {
        if(vel.x<0) changeTextureRect(1);
        else if(vel.x>0) changeTextureRect(3);
        else changeTextureRect(0);
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

    if(vh::distance(desiredPos,getPosition())>10)
    {
        if(vel.y<0) vel.y-=offsetY/2;
        else if(vel.y>0) vel.y+=offsetY/2;
        if(vel.x>0) vel.x-=abs(vel.y)/2;
        else if(vel.x<0) vel.x+=abs(vel.y)/2;
    }
    if(vel.x==0&&vel.y==0) wandering=false;
    else wandering=true;
    move(vel.x,vel.y);
}

void Entity::changeTextureRect(int value)
{
    sf::IntRect t(0,BLOCK_SIZE*value,BLOCK_SIZE,BLOCK_SIZE);
    setTextureRect(t);
}

void Entity::update()
{
    if(!wandering&&wanderClock.getElapsedTime().asMilliseconds()>3275)
    {
        wanderClock.restart();
        wander();
    }
    moving();
}
