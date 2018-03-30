#ifndef EQUIPMENT_H_INCLUDED
#define EQUIPMENT_H_INCLUDED
#include "globals.h"
#include <vector>
using namespace std;

class Item : public sf::Sprite
{
    int id;
public:
    Item(int id):id(id){};
    void draw(sf::RenderWindow& window){window.draw(*this);};
};

class Equipment
{
    vector<Item*> items;
public:
    Equipment();
    void add(Item* item);
    void rmv(Item* item);
};

#endif // EQUIPMENT_H_INCLUDED
