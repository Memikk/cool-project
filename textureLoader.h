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
    sf::Texture* tree;
    sf::Texture* plants;
public:
    TextureLoader(){};
    void load()
    {
        player=new sf::Texture();
        sand=new sf::Texture();
        water=new sf::Texture();
        stone=new sf::Texture();
        tree=new sf::Texture();
        plants=new sf::Texture();
        if(player->loadFromFile("player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(sand->loadFromFile("sand.png")) cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("water.png")) cout<<"Wczytano teksture wody"<<endl;
        if(stone->loadFromFile("stone.png")) cout<<"Wczytano teksture wody"<<endl;
        if(tree->loadFromFile("tree.png")) cout<<"Wczytano teksture drzewa"<<endl;
        if(plants->loadFromFile("plants.png")) cout<<"Wczytano teksture roslin"<<endl;
    }
    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.setScale(50/20.0,50/20.0);
    }
    void setSandTexture(Block& s,int x)
    {
        sf::IntRect temp(0,50*x,50,50);
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
    void setTreeTexture(Block& t)
    {
        t.setObjectTexture(*tree);
    }
    void setPlantTexture(Block& t)
    {
        t.setObjectTexture(*plants,rand()%13);
    }
};

#endif // TEXTURELOADER_H_INCLUDED
