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
    sf::Texture* eq;
    sf::Texture* popUp;

    sf::Texture* sand;
    sf::Texture* water;
    sf::Texture* stone;
    sf::Texture* grass;
    sf::Texture* dirt;
    sf::Texture* tree;
    sf::Texture* bush;
    sf::Texture* plants;

    sf::Texture* sheep;
    sf::Texture* cow;
    sf::Texture* pig;

    sf::Texture* hpBar;
    sf::Texture* hungerBar;
    sf::Texture* thirstBar;

    sf::Texture* branch;
    sf::Texture* rock;
public:
    vector<sf::Texture*> items;
    TextureLoader(){};
    void load()
    {
        player=new sf::Texture();
        eq=new sf::Texture();
        popUp=new sf::Texture();
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
        hpBar=new sf::Texture();
        hungerBar=new sf::Texture();
        thirstBar=new sf::Texture();
        branch=new sf::Texture();
        rock=new sf::Texture();
        bush=new sf::Texture();
        if(player->loadFromFile("resources/textures/player.png")) cout<<"Wczytano teksture gracza"<<endl;
        if(eq->loadFromFile("resources/textures/eq.png")) cout<<"Wczytano teksture ekwipunku"<<endl;
        if(popUp->loadFromFile("resources/textures/popup.png")) cout<<"Wczytano teksture popupu"<<endl;
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
        if(hpBar->loadFromFile("resources/textures/hpBar.png")) cout<<"Wczytano teksture paska zycia"<<endl;
        if(hungerBar->loadFromFile("resources/textures/hungerBar.png")) cout<<"Wczytano teksture paska g�odu"<<endl;
        if(thirstBar->loadFromFile("resources/textures/thirstBar.png")) cout<<"Wczytano teksture paska pragnienia"<<endl;
        if(branch->loadFromFile("resources/textures/branch.png")) cout<<"Wczytano teksture galazki"<<endl;
        if(rock->loadFromFile("resources/textures/rock.png")) cout<<"Wczytano teksture kamyka"<<endl;
        if(bush->loadFromFile("resources/textures/bush.png")) cout<<"Wczytano teksture krzaka"<<endl;
        items.push_back(branch);
        items.push_back(rock);
    }

    void chooseTexture(Block& block,int i,int j,int offsetX,int offsetY,blockType type,float value);
    void setTexture(Block& block,blockType type,int choice);
    void chooseTexture(Object& object,int i,int j,int offsetX,int offsetY,objectType type,float value,siv::PerlinNoise& perlin);
    void setTexture(Object& object,objectType type,int choice);

    void chooseTexture(Block& block,vector<Block*> n);

    void setTexture(Entity& entity,entityType);

    void setPlayerTexture(Player& p)
    {
        p.setTexture(*player);
        p.hpBar.setTexture(*hpBar);
        p.hungerBar.setTexture(*hungerBar);
        p.thirstBar.setTexture(*thirstBar);
        p.eq.setTexture(*eq);
        p.setScale(0.85,0.85);
    }

    void setItemTexture(Item& i,int choice)
    {
        switch(choice)
        {
        case 0:
            i.setTexture(*branch);
            break;
        case 1:
            i.setTexture(*rock);
            break;
        }
    }

    sf::Texture* getPopUpTexture()
    {
        return popUp;
    }

    sf::Texture* getItemTexture(int id)
    {
        return items[id];
    }
};

#endif // TEXTURELOADER_H_INCLUDED
