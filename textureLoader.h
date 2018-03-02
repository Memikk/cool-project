#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED
#include <iostream>
#include "globals.h"
using namespace std;

class TextureLoader
{
    sf::Texture* player;
    sf::Texture* sand;
public:
    TextureLoader(){};
    void load()
    {
        player=new sf::Texture();
        sand=new sf::Texture();
        cout<<"LADOWANIE TEKSTUR"<<endl;
        if(player->loadFromFile("player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(sand->loadFromFile("sand.png")) cout<<"Wczytano teksture piasku"<<endl;;
        cout<<"KONIEC LADOWANIA TEKSTUR"<<endl;
    }
    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.setScale(50/32.0,50/32.0);
    }
    void setSandTexture(Block& s,int x)
    {
        cout<<"set sand texture"<<endl;
        sf::IntRect temp(0,10*x,10,10);
        s.setTextureRect(temp);
        s.setTexture(sand);
        //s.setScale(5,5);
        cout<<"end"<<endl;
    }
};

#endif // TEXTURELOADER_H_INCLUDED
