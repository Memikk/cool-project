#include "entities.h"

void Entity::wander()
{
    int x,y;
    x=(rand())%200;
    x*=((rand()%2==0)?-1:1);
    y=(rand())%200;
    y*=((rand()%2==0)?-1:1);

    desiredPos.x=x+getPosition().x;
    desiredPos.y=y+getPosition().y;
}

void Entity::moving(vector<Block*> collisions)
{
    float offsetY = (sin(vh::distance(desiredPos,getPosition())*16*M_PI/180));
    if(abs(desiredPos.x-getPosition().x)<2)
    {
        vel.x=0;
    }
    else
        vel.x=(desiredPos.x>getPosition().x)?1:-1;
    if(abs(desiredPos.y-getPosition().y)<2)
    {
        vel.y=0;
    }
    else
        vel.y=(desiredPos.y>getPosition().y)?1:-1;

    if(vel.y<0)
    {
        if(vel.x<0)
            changeTextureRect(1);
        else if(vel.x>0)
            changeTextureRect(3);
        else
            changeTextureRect(2);
    }
    else
    {
        if(vel.x<0)
            changeTextureRect(1);
        else if(vel.x>0)
            changeTextureRect(3);
        else
            changeTextureRect(0);
    }

    for(auto& c:collisions)
    {
        sf::Sprite temp1=*this;
        sf::Sprite temp2=*this;

        temp1.move(vel.x,0);
        if(c->collision&&temp1.getGlobalBounds().intersects(c->getGlobalBounds()))
        {
            vel.x=0;
            desiredPos=getPosition();
        }
        temp2.move(0,vel.y);
        if(c->collision&&temp2.getGlobalBounds().intersects(c->getGlobalBounds()))
        {
            vel.y=0;
            desiredPos=getPosition();
        }
    }

    //JUMPING
    if(vh::distance(desiredPos,getPosition())>10)
    {
        if(vel.y<0)
            vel.y-=offsetY/2;
        else if(vel.y>0)
            vel.y+=offsetY/2;
        else
            vel.y+=offsetY/2.4;
        if(vel.x>0)
            vel.x-=abs(vel.y)/2.4;
        else if(vel.x<0)
            vel.x+=abs(vel.y)/2.4;
    }
    if(vel.x==0&&vel.y==0)
        wandering=false;
    else
        wandering=true;
    move(vel.x,vel.y);
}

void Entity::changeTextureRect(int value)
{
    sf::IntRect t(0,BLOCK_SIZE*value,BLOCK_SIZE,BLOCK_SIZE);
    setTextureRect(t);
}

void Entity::update(vector<Block*> collisions)
{
    counter++;
    if(!wandering&&counter>300+rand()%180)
    {
        //wanderClock.restart();
        counter=0;
        wander();
    }
    moving(collisions);
}
