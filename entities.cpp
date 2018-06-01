#include "entities.h"

void Entity::wander()
{
    int x,y;
    x=(rand())%200-100;
    y=(rand())%200-100;
    cerr<<"x="<<x<<endl<<"y="<<y<<endl;

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

void Wolf::update(vector<Block*> collisions,vector<Entity*>& entities,Player& player)
{
    hungry=(hungerCounter?false:true);
    if(hungerCounter) hungerCounter--;
    if(hungry)
    {
        float tempD=999999;
        sf::Vector2f desiredTemp;
        float playerDistance=vh::distance(getPosition(),player.getPosition());

        if(attackCooldown==110)
            player.setColor(sf::Color::White);
        if(attackCooldown>0)
            attackCooldown--;

        if(playerDistance<150&&player.hp>0)
        {
            desiredPos=player.getPosition();
            if(attackCooldown==0&&playerDistance<30)
            {
                player.hp-=damage;
                player.setColor(sf::Color::Red);
                player.hpCover.setSize(sf::Vector2f(120-player.hp*1.2,player.hpCover.getSize().y));
                cout<<"PLAYER HP="<<player.hp<<endl;
                attackCooldown=2*60;
            }
            else
            {
                moving(collisions);
            }
            return;
        }

        for(int i=entities.size()-1; i>=0; i--)
        {
            float d=0;
            if(entities[i]->type!=WOLF)
                d=vh::distance(getPosition(),entities[i]->getPosition());
            else
                continue;
            if(d<tempD)
            {
                tempD=d;
                desiredTemp=entities[i]->getPosition();
            }
            if(d<10)
            {
                hungerCounter=7200;
                Entity* temp=entities[i];
                if(temp!=nullptr)
                {
                    Item* it = new Item(ITEMS::MEAT);
                    it->food=true;
                    it->setTexture(*txtLoader->getItemTexture(2));

                    if(temp->block!=nullptr)
                    {
                        it->setPosition(temp->block->getPosition());
                        temp->block->items.push_back(it);
                    }
                    entities.erase(entities.begin()+i);
                    //delete temp;
                }
                break;
            }
        }
        desiredPos=desiredTemp;
        moving(collisions);
    }
    else
    {
        static_cast<Entity*>(this)->update(collisions);
    }
}
