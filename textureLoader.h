#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED
#include <iostream>
#include "globals.h"
using namespace std;

class TextureLoader
{
    sf::Texture* player;
    sf::Texture* sand;
    sf::Texture* water;
public:
    TextureLoader(){};
    void load()
    {
        player=new sf::Texture();
        sand=new sf::Texture();
        water=new sf::Texture();
        if(player->loadFromFile("player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(sand->loadFromFile("sand.png")) cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("water.png")) cout<<"Wczytano teksture wody"<<endl;
    }
    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.setScale(50/32.0,50/32.0);
    }
    void setSandTexture(Block& s,int x)
    {
        sf::IntRect temp(0,10*x,10,10);
        s.setTextureRect(temp);
        s.setTexture(sand);
    }
    void setWaterTexture(Block& w)
    {
        sf::IntRect temp(0,0,10,10);
        w.setTextureRect(temp);
        w.setTexture(water);
    }
};

#endif // TEXTURELOADER_H_INCLUDED
