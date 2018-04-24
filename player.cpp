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
    hungerBar.setScale(3,3);
    thirstBar.setScale(3,3);
    hpCover.setPosition(hpBar.getPosition()+sf::Vector2f(40,5));
    hungerCover.setPosition(hungerBar.getPosition()+sf::Vector2f(40,5));
    thirstCover.setPosition(thirstBar.getPosition()+sf::Vector2f(40,5));
    hpCover.setSize(sf::Vector2f(120/hp,10));
    hungerCover.setSize(sf::Vector2f(120/hp,10));
    thirstCover.setSize(sf::Vector2f(120/hp,10));
    hpCover.setFillColor(sf::Color::Black);
    hungerCover.setFillColor(sf::Color::Black);
    thirstCover.setFillColor(sf::Color::Black);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Player::update(vector<Block*>& collisions)
{
    if(eq.bar.size()>eq.selectedSlot&&eq.bar[eq.selectedSlot]->building)
    {
        if(dir==UP&&collisions[1]->object==nullptr)
        {
            if(collisions[1]->cover)collisions[1]->cover->setColor(sf::Color(0,255,0,50));
            if(collisions[1]->grass)collisions[1]->grass->setColor(sf::Color(0,255,0,50));
            if(collisions[1])collisions[1]->setFillColor(sf::Color(0,255,0,50));
        }
        if(dir==RIGHT&&collisions[3]->object==nullptr)
        {
            if(collisions[3]->cover)collisions[3]->cover->setColor(sf::Color(0,255,0,50));
            if(collisions[3]->grass)collisions[3]->grass->setColor(sf::Color(0,255,0,50));
            if(collisions[3])collisions[3]->setFillColor(sf::Color(0,255,0,50));
        }
        if(dir==DOWN&&collisions[5]->object==nullptr)
        {
            if(collisions[5]->cover)collisions[5]->cover->setColor(sf::Color(0,255,0,50));
            if(collisions[5]->grass)collisions[5]->grass->setColor(sf::Color(0,255,0,50));
            if(collisions[5])collisions[5]->setFillColor(sf::Color(0,255,0,50));
        }
        if(dir==LEFT&&collisions[7]->object==nullptr)
        {
            if(collisions[7]->cover)collisions[7]->cover->setColor(sf::Color(0,255,0,50));
            if(collisions[7]->grass)collisions[7]->grass->setColor(sf::Color(0,255,0,50));
            if(collisions[7])collisions[7]->setFillColor(sf::Color(0,255,0,50));
        }
    }
    //cout<<"--------------------PLAYER UPDATE-------------------"<<endl;
    moving(collisions);
    //cout<<"PO RUCHU GRACZA"<<endl;
    animate(collisions);
    //cout<<"PO ANIMACJI GRACZA"<<endl;
    counter++;
    if(counter==5*60)
    {
        if(hunger>50&&thirst>50&&hp<100)
        {
            hp+=5;
        }
        if(hunger>0)hunger--;
        else if(hp>0)hp-=5;
        if(thirst>0)thirst--;
        else if(hp>0)hp-=5;
        hpCover.setSize(sf::Vector2f(120-hp*1.2,hpCover.getSize().y));
        hungerCover.setSize(sf::Vector2f(120-hunger*1.2,hungerCover.getSize().y));
        thirstCover.setSize(sf::Vector2f(120-thirst*1.2,thirstCover.getSize().y));
        counter=0;
    }
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
            vel.y*=0.80;
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
            vel.x*=0.80;
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
    sf::IntRect t(0,33*value,23,33);
    setTextureRect(t);
}

void Player::animate(vector<Block*>& collisions)
{
    move(vel);
    background.setPosition(getPosition()-background.getSize()/2.f);
}
