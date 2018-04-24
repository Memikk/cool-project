#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED
#include "globals.h"
#include <vector>
using namespace std;

enum class ITEMS{BRANCH=0,ROCK,MEAT,WHEAT,CARROT,LOG,AXE,PLANKS,PICKAXE,WOODENWALLITEM};
class Item : public sf::Sprite
{
public:
    bool food=false;
    bool building=false;
    ITEMS id;
    Item(ITEMS id):id(id)
    {
        if(id==ITEMS::PLANKS||id==ITEMS::WOODENWALLITEM)
        {
            building=true;
        }
    }
    void draw(sf::RenderWindow& window){window.draw(*this);};
};

class Equipment : public sf::Sprite
{
public:
    unsigned selectedSlot=0;
    Item* itemHolder=nullptr;
    Item* itemFromCrafting=nullptr;
    vector<sf::RectangleShape> slots;
    sf::Sprite itemsBar;
    sf::Sprite itemFrame;
    vector<Item*> crafting;
    vector<Item*> items;
    vector<Item*> bar;
    void changeSlot(unsigned);
    void checkRecipes(vector<sf::Texture*>& v);
    bool on=false;
    Equipment();
    void add(Item* item);
    void rmv(Item* item);
};

#endif // EQUIPMENT_H_INCLUDED
