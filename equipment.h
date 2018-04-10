#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED
#include "globals.h"
#include <vector>
using namespace std;

class Item : public sf::Sprite
{
public:
    bool food=false;
    int id;
    Item(int id):id(id){};
    void draw(sf::RenderWindow& window){window.draw(*this);};
};

class Equipment : public sf::Sprite
{
public:
    vector<Item*> items;
    bool on=false;
    Equipment();
    void add(Item* item);
    void rmv(Item* item);
};

#endif // EQUIPMENT_H_INCLUDED
