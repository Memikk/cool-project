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
    sf::Texture* grass;
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
        grass=new sf::Texture();
        tree=new sf::Texture();
        plants=new sf::Texture();
        if(player->loadFromFile("player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(sand->loadFromFile("sand.png")) cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("water.png")) cout<<"Wczytano teksture wody"<<endl;
        if(stone->loadFromFile("stone.png")) cout<<"Wczytano teksture kamienia"<<endl;
        if(grass->loadFromFile("grass.png")) cout<<"Wczytano teksture trawy"<<endl;
        if(tree->loadFromFile("tree.png")) cout<<"Wczytano teksture drzewa"<<endl;
        if(plants->loadFromFile("plants.png")) cout<<"Wczytano teksture roslin"<<endl;
    }
    void chooseTexture(Block& block,int i,int j,int offsetX,int offsetY,blockType type,float value);
    void setTexture(Block& block,blockType type,int choice);
    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.setScale(25/20.0,25/20.0);
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
