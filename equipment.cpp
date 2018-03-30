#include "equipment.h"

Equipment::Equipment()
{
    items.reserve(20);
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
