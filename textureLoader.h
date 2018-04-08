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
    sf::Texture* cursor;

    sf::Texture* sand;
    sf::Texture* water;
    sf::Texture* stone;
    sf::Texture* grass;
    sf::Texture* dirt;
    sf::Texture* tree;
    sf::Texture* bush;
    sf::Texture* wheat;
    sf::Texture* carrot;

    sf::Texture* sheep;
    sf::Texture* cow;
    sf::Texture* pig;
    sf::Texture* wolf;

    sf::Texture* hpBar;
    sf::Texture* hungerBar;
    sf::Texture* thirstBar;

    sf::Texture* branch;
    sf::Texture* rock;
    sf::Texture* meat;
    sf::Texture* wheatItem;
    sf::Texture* carrotItem;
public:
    vector<sf::Texture*> items;
    TextureLoader() {};
    void load()
    {
        player=new sf::Texture();
        eq=new sf::Texture();
        popUp=new sf::Texture();
        cursor=new sf::Texture();
        sand=new sf::Texture();
        water=new sf::Texture();
        stone=new sf::Texture();
        grass=new sf::Texture();
        dirt=new sf::Texture();
        tree=new sf::Texture();
        sheep=new sf::Texture();
        cow=new sf::Texture();
        wolf=new sf::Texture();
        pig=new sf::Texture();
        hpBar=new sf::Texture();
        hungerBar=new sf::Texture();
        thirstBar=new sf::Texture();
        branch=new sf::Texture();
        rock=new sf::Texture();
        meat=new sf::Texture();
        wheatItem=new sf::Texture();
        carrotItem=new sf::Texture();
        bush=new sf::Texture();
        wheat=new sf::Texture();
        carrot=new sf::Texture();
        if(player->loadFromFile("resources/textures/player.png"))
            cout<<"Wczytano teksture gracza"<<endl;
        if(eq->loadFromFile("resources/textures/eq.png"))
            cout<<"Wczytano teksture ekwipunku"<<endl;
        if(popUp->loadFromFile("resources/textures/popup.png"))
            cout<<"Wczytano teksture popupu"<<endl;
        if(cursor->loadFromFile("resources/textures/cursor.png"))
            cout<<"Wczytano teksture kursora"<<endl;
        if(sand->loadFromFile("resources/textures/sand.png"))
            cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("resources/textures/water.png"))
            cout<<"Wczytano teksture wody"<<endl;
        if(stone->loadFromFile("resources/textures/stone.png"))
            cout<<"Wczytano teksture kamienia"<<endl;
        if(grass->loadFromFile("resources/textures/grass.png"))
            cout<<"Wczytano teksture trawy"<<endl;
        if(dirt->loadFromFile("resources/textures/dirt.png"))
            cout<<"Wczytano teksture ziemi"<<endl;
        if(tree->loadFromFile("resources/textures/tree.png"))
            cout<<"Wczytano teksture drzewa"<<endl;
        if(sheep->loadFromFile("resources/textures/sheep.png"))
            cout<<"Wczytano teksture owcy"<<endl;
        if(cow->loadFromFile("resources/textures/cow.png"))
            cout<<"Wczytano teksture krowy"<<endl;
        if(pig->loadFromFile("resources/textures/pig.png"))
            cout<<"Wczytano teksture swini"<<endl;
        if(hpBar->loadFromFile("resources/textures/hpBar.png"))
            cout<<"Wczytano teksture paska zycia"<<endl;
        if(hungerBar->loadFromFile("resources/textures/hungerBar.png"))
            cout<<"Wczytano teksture paska glodu"<<endl;
        if(thirstBar->loadFromFile("resources/textures/thirstBar.png"))
            cout<<"Wczytano teksture paska pragnienia"<<endl;
        if(branch->loadFromFile("resources/textures/branch.png"))
            cout<<"Wczytano teksture galazki"<<endl;
        if(rock->loadFromFile("resources/textures/rock.png"))
            cout<<"Wczytano teksture kamyka"<<endl;
        if(meat->loadFromFile("resources/textures/meat.png"))
            cout<<"Wczytano teksture miesa"<<endl;
        if(wheatItem->loadFromFile("resources/textures/wheatItem.png"))
            cout<<"Wczytano teksture pszenicy(przedmiot)"<<endl;
        if(carrotItem->loadFromFile("resources/textures/carrotItem.png"))
            cout<<"Wczytano teksture marchewki(przedmiot)"<<endl;
        if(bush->loadFromFile("resources/textures/bush.png"))
            cout<<"Wczytano teksture krzaka"<<endl;
        if(wheat->loadFromFile("resources/textures/wheat.png"))
            cout<<"Wczytano teksture pszenicy"<<endl;
        if(carrot->loadFromFile("resources/textures/carrot.png"))
            cout<<"Wczytano teksture marchewki"<<endl;
        if(wolf->loadFromFile("resources/textures/wolf.png"))
            cout<<"Wczytano teksture wilka"<<endl;
        items.push_back(branch);
        items.push_back(rock);
        items.push_back(meat);
        items.push_back(wheatItem);
        items.push_back(carrotItem);
    }

    void chooseTexture(Block& block,int i,int j,int offsetX,int offsetY,blockType type,float value);
    void setTexture(Block& block,blockType type,int choice);
    void chooseTexture(Object& object,int i,int j,int offsetX,int offsetY,objectType type,float value,siv::PerlinNoise& perlin);
    void setTexture(Object& object,objectType type,int choice);

    void chooseTexture(Block& block,vector<Block*> n);

//    void setTexture(Entity& entity,entityType);

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
        case 2:
            i.setTexture(*meat);
            break;
        case 3:
            i.setTexture(*wheatItem);
            break;
        case 4:
            i.setTexture(*carrotItem);
            break;
        }
    }

    sf::Texture* getPopUpTexture()
    {
        return popUp;
    }

    sf::Texture* getEntityTexture(int type)
    {
        switch(type)
        {
        case 0:
            return sheep;
            break;
        case 1:
            return cow;
            break;
        case 2:
            return pig;
            break;
        case 3:
            return wolf;
            break;
        default:
            return nullptr;
            break;
        }
    }

    sf::Texture* getItemTexture(int id)
    {
        return items[id];
    }

    sf::Texture* getCursorTexture()
    {
        return cursor;
    }
};

#endif // TEXTURELOADER_H_INCLUDED
