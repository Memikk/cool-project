#include "equipment.h"

Equipment::Equipment()
{
    items.reserve(20);
    for(int i=0;i<20;i++)
    {
        sf::RectangleShape temp(sf::Vector2f(25,25));
        slots.push_back(temp);
    }
}

void Equipment::add(Item* item)
{
    items.push_back(item);
}

void Equipment::rmv(Item* item)
{
    for(auto& i:items)
    {
        if(i==item)
        {
            delete i;
            break;
        }
    }
}
