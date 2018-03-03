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
    sf::Texture* stone;
public:
    TextureLoader(){};
    void load()
    {
        player=new sf::Texture();
        sand=new sf::Texture();
        water=new sf::Texture();
        stone=new sf::Texture();
        if(player->loadFromFile("player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(sand->loadFromFile("sand.png")) cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("water.png")) cout<<"Wczytano teksture wody"<<endl;
        if(stone->loadFromFile("stone.png")) cout<<"Wczytano teksture wody"<<endl;
    }
    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.setScale(50/20.0,50/20.0);
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
    void setStoneTexture(Block& s,int x)
    {
        sf::IntRect temp(0,50*x,50,50);
        s.setTextureRect(temp);
        s.setTexture(stone);
    }
};

#endif // TEXTURELOADER_H_INCLUDED
