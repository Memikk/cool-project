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
    sf::Texture* popUpPick;
    sf::Texture* popUpDrop;
    sf::Texture* cursor;

    sf::Texture* sand;
    sf::Texture* water;
    sf::Texture* stone;
    sf::Texture* grass;
    sf::Texture* dirt;
    sf::Texture* tree;
    sf::Texture* decoratives;
    sf::Texture* animatedPlant;
    sf::Texture* bush;
    sf::Texture* berrybush;
    sf::Texture* wheat;
    sf::Texture* carrot;

    sf::Texture* sheep;
    sf::Texture* cow;
    sf::Texture* pig;
    sf::Texture* wolf;
    sf::Texture* rabbit;

    sf::Texture* hpBar;
    sf::Texture* hungerBar;
    sf::Texture* thirstBar;
    sf::Texture* itemsBar;
    sf::Texture* itemFrame;

    sf::Texture* branch;
    sf::Texture* log;
    sf::Texture* planks;
    sf::Texture* rock;
    sf::Texture* meat;
    sf::Texture* wheatItem;
    sf::Texture* carrotItem;
    sf::Texture* berries;
    sf::Texture* axe;
    sf::Texture* pickaxe;
    sf::Texture* woodenWallItem;
    sf::Texture* stoneFloorItem;
    sf::Texture* stoneWallItem;

    sf::Texture* woodenFloor;
    sf::Texture* woodenWall;
    sf::Texture* stoneWall;
    sf::Texture* stoneFloor;
public:
    vector<sf::Texture*> items;
    TextureLoader() {};
    void load()
    {
        player=new sf::Texture();
        eq=new sf::Texture();
        popUpPick=new sf::Texture();
        popUpDrop=new sf::Texture();
        cursor=new sf::Texture();
        sand=new sf::Texture();
        water=new sf::Texture();
        stone=new sf::Texture();
        grass=new sf::Texture();
        dirt=new sf::Texture();
        tree=new sf::Texture();
        decoratives=new sf::Texture();
        sheep=new sf::Texture();
        cow=new sf::Texture();
        wolf=new sf::Texture();
        rabbit=new sf::Texture();
        pig=new sf::Texture();
        hpBar=new sf::Texture();
        hungerBar=new sf::Texture();
        thirstBar=new sf::Texture();
        itemsBar=new sf::Texture();
        itemFrame=new sf::Texture();
        branch=new sf::Texture();
        log=new sf::Texture();
        planks=new sf::Texture();
        rock=new sf::Texture();
        meat=new sf::Texture();
        wheatItem=new sf::Texture();
        carrotItem=new sf::Texture();
        bush=new sf::Texture();
        berrybush=new sf::Texture();
        wheat=new sf::Texture();
        carrot=new sf::Texture();
        berries=new sf::Texture();
        axe=new sf::Texture();
        pickaxe=new sf::Texture();
        woodenWallItem=new sf::Texture();
        woodenFloor=new sf::Texture();
        woodenWall=new sf::Texture();
        stoneWallItem=new sf::Texture();
        stoneFloorItem=new sf::Texture();
        stoneFloor=new sf::Texture();
        stoneWall=new sf::Texture();
        animatedPlant=new sf::Texture();
        if(player->loadFromFile("resources/textures/player.png"))cout<<"Wczytano teksture gracza"<<endl;
        if(eq->loadFromFile("resources/textures/eq.png"))cout<<"Wczytano teksture ekwipunku"<<endl;
        if(popUpPick->loadFromFile("resources/textures/popup.png"))cout<<"Wczytano teksture powiadomienia o podniesieniu przedmiotu"<<endl;
        if(popUpDrop->loadFromFile("resources/textures/popupdrop.png"))cout<<"Wczytano teksture powiadomienia o upuszczeniu przedmiotu"<<endl;
        if(cursor->loadFromFile("resources/textures/cursor.png"))cout<<"Wczytano teksture kursora"<<endl;
        if(sand->loadFromFile("resources/textures/sand.png"))cout<<"Wczytano teksture piasku"<<endl;
        if(water->loadFromFile("resources/textures/water.png"))cout<<"Wczytano teksture wody"<<endl;
        if(stone->loadFromFile("resources/textures/stone.png"))cout<<"Wczytano teksture kamienia"<<endl;
        if(grass->loadFromFile("resources/textures/grass.png"))cout<<"Wczytano teksture trawy"<<endl;
        if(dirt->loadFromFile("resources/textures/dirt.png"))cout<<"Wczytano teksture ziemi"<<endl;
        if(tree->loadFromFile("resources/textures/tree.png"))cout<<"Wczytano teksture drzewa"<<endl;
        if(decoratives->loadFromFile("resources/textures/decoratives.png"))cout<<"Wczytano teksture ozdob"<<endl;
        if(sheep->loadFromFile("resources/textures/sheep.png"))cout<<"Wczytano teksture owcy"<<endl;
        if(cow->loadFromFile("resources/textures/cow.png"))cout<<"Wczytano teksture krowy"<<endl;
        if(pig->loadFromFile("resources/textures/pig.png"))cout<<"Wczytano teksture swini"<<endl;
        if(hpBar->loadFromFile("resources/textures/hpBar.png"))cout<<"Wczytano teksture paska zycia"<<endl;
        if(hungerBar->loadFromFile("resources/textures/hungerBar.png"))cout<<"Wczytano teksture paska glodu"<<endl;
        if(thirstBar->loadFromFile("resources/textures/thirstBar.png"))cout<<"Wczytano teksture paska pragnienia"<<endl;
        if(itemsBar->loadFromFile("resources/textures/itemsBar.png"))cout<<"Wczytano teksture paska przedmiotow"<<endl;
        if(itemFrame->loadFromFile("resources/textures/frame.png"))cout<<"Wczytano teksture obramowania wybranego przedmiotu"<<endl;
        if(branch->loadFromFile("resources/textures/branch.png"))cout<<"Wczytano teksture galazki"<<endl;
        if(log->loadFromFile("resources/textures/log.png"))cout<<"Wczytano teksture klody"<<endl;
        if(planks->loadFromFile("resources/textures/planks.png"))cout<<"Wczytano teksture desek"<<endl;
        if(rock->loadFromFile("resources/textures/rock.png"))cout<<"Wczytano teksture kamyka"<<endl;
        if(meat->loadFromFile("resources/textures/meat.png"))cout<<"Wczytano teksture miesa"<<endl;
        if(wheatItem->loadFromFile("resources/textures/wheatItem.png"))cout<<"Wczytano teksture pszenicy(przedmiot)"<<endl;
        if(carrotItem->loadFromFile("resources/textures/carrotItem.png"))cout<<"Wczytano teksture marchewki(przedmiot)"<<endl;
        if(bush->loadFromFile("resources/textures/bush.png"))cout<<"Wczytano teksture krzaka"<<endl;
        if(berrybush->loadFromFile("resources/textures/berrybush.png"))cout<<"Wczytano teksture krzaka z jagodami"<<endl;
        if(wheat->loadFromFile("resources/textures/wheat.png"))cout<<"Wczytano teksture pszenicy"<<endl;
        if(carrot->loadFromFile("resources/textures/carrot.png"))cout<<"Wczytano teksture marchewki"<<endl;
        if(berries->loadFromFile("resources/textures/berries.png"))cout<<"Wczytano teksture jagod"<<endl;
        if(wolf->loadFromFile("resources/textures/wolf.png"))cout<<"Wczytano teksture wilka"<<endl;
        if(rabbit->loadFromFile("resources/textures/rabbit.png"))cout<<"Wczytano teksture krolika"<<endl;
        if(axe->loadFromFile("resources/textures/axe.png"))cout<<"Wczytano teksture siekiery"<<endl;
        if(pickaxe->loadFromFile("resources/textures/pickaxe.png"))cout<<"Wczytano teksture siekiery"<<endl;
        if(woodenWallItem->loadFromFile("resources/textures/woodenWallItem.png"))cout<<"Wczytano teksture przedmiotu drewnianej sciany"<<endl;
        if(woodenFloor->loadFromFile("resources/textures/woodenFloor.png"))cout<<"Wczytano teksture drewnianej podlogi"<<endl;
        if(woodenWall->loadFromFile("resources/textures/woodenWall.png"))cout<<"Wczytano teksture drewnianej sciany"<<endl;
        if(stoneWall->loadFromFile("resources/textures/stonewall.png"))cout<<"Wczytano teksture drewnianej sciany"<<endl;
        if(stoneFloor->loadFromFile("resources/textures/stonefloor.png"))cout<<"Wczytano teksture drewnianej sciany"<<endl;
        if(stoneWallItem->loadFromFile("resources/textures/stonewallitem.png"))cout<<"Wczytano teksture drewnianej sciany"<<endl;
        if(stoneFloorItem->loadFromFile("resources/textures/stoneflooritem.png"))cout<<"Wczytano teksture drewnianej sciany"<<endl;
        if(animatedPlant->loadFromFile("resources/textures/plant.png"))cout<<"Wczytano teksture roslinki"<<endl;

        items.push_back(branch); //0
        items.push_back(rock); //1
        items.push_back(meat); //2
        items.push_back(wheatItem); //3
        items.push_back(carrotItem); //4
        items.push_back(log); //5
        items.push_back(axe); //6
        items.push_back(planks); //7
        items.push_back(pickaxe); //8
        items.push_back(woodenWallItem); //9
        items.push_back(berries); //10
        items.push_back(stoneWallItem); //11
        items.push_back(stoneFloorItem); //12
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
        p.eq.itemsBar.setTexture(*itemsBar);
        p.eq.itemFrame.setTexture(*itemFrame);
        p.setScale(0.85,0.85);
    }

    void setTreeTexture(Object& obj)
    {
        obj.setTexture(*tree);
    }
    void setDecorationTexture(Object& obj,int choice)
    {
        obj.setTexture(*decoratives);
        obj.setTextureRect(sf::IntRect(0,50*choice,50,50));
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
        case 5:
            i.setTexture(*log);
            break;
        case 6:
            i.setTexture(*axe);
            break;
        case 7:
            i.setTexture(*planks);
            break;
        case 8:
            i.setTexture(*pickaxe);
            break;
        case 9:
            i.setTexture(*woodenWallItem);
            break;
        case 10:
            i.setTexture(*berries);
            break;
        case 11:
            i.setTexture(*stoneWallItem);
            break;
        case 12:
            i.setTexture(*stoneFloor);
            break;
        }
    }

    vector<sf::Texture*>& AllItems()
    {
        return items;
    }

    sf::Texture* getPopUpPickTexture()
    {
        return popUpPick;
    }

    sf::Texture* getPopUpDropTexture()
    {
        return popUpDrop;
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
        case 4:
            return rabbit;
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
