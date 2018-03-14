#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED
#include <iostream>
#include "globals.h"
#include "player.h"
#include "entities.h"

using namespace std;

class TextureLoader
{
    sf::Texture* player;
    sf::Texture* sand;
    sf::Texture* water;
    sf::Texture* stone;
    sf::Texture* grass;
    sf::Texture* dirt;
    sf::Texture* tree;
    sf::Texture* plants;

    sf::Texture* sheep;
    sf::Texture* cow;
    sf::Texture* pig;
public:
    TextureLoader(){};
    void load()
    {
        player=new sf::Texture();
        sand=new sf::Texture();
        water=new sf::Texture();
        stone=new sf::Texture();
        grass=new sf::Texture();
        dirt=new sf::Texture();
        tree=new sf::Texture();
        plants=new sf::Texture();
        sheep=new sf::Texture();
        cow=new sf::Texture();
        pig=new sf::Texture();
        if(player->loadFromFile("resources/textures/player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(sand->loadFromFile("resources/textures/sand.png")) cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("resources/textures/water.png")) cout<<"Wczytano teksture wody"<<endl;
        if(stone->loadFromFile("resources/textures/stone.png")) cout<<"Wczytano teksture kamienia"<<endl;
        if(grass->loadFromFile("resources/textures/grass.png")) cout<<"Wczytano teksture trawy"<<endl;
        if(dirt->loadFromFile("resources/textures/dirt.png")) cout<<"Wczytano teksture ziemi"<<endl;
        if(tree->loadFromFile("resources/textures/tree.png")) cout<<"Wczytano teksture drzewa"<<endl;
        if(plants->loadFromFile("resources/textures/plants.png")) cout<<"Wczytano teksture roslin"<<endl;
        if(sheep->loadFromFile("resources/textures/sheep.png")) cout<<"Wczytano teksture owcy"<<endl;
        if(cow->loadFromFile("resources/textures/cow.png")) cout<<"Wczytano teksture krowy"<<endl;
        if(pig->loadFromFile("resources/textures/pig.png")) cout<<"Wczytano teksture swini"<<endl;
    }

    void chooseTexture(Block& block,int i,int j,int offsetX,int offsetY,blockType type,float value);
    void setTexture(Block& block,blockType type,int choice);
    void chooseTexture(Object& object,int i,int j,int offsetX,int offsetY,objectType type,float value);
    void setTexture(Object& object,objectType type,int choice);

    void setTexture(Entity& entity,entityType);

    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.setScale(25/20.0,25/20.0);
    }
};

#endif // TEXTURELOADER_H_INCLUDED
