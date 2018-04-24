#include "equipment.h"

Equipment::Equipment()
{
    items.reserve(20);
    crafting.reserve(4);
    bar.reserve(5);
    for(int i=0;i<30;i++)
    {
        sf::RectangleShape temp(sf::Vector2f(25,25));
        temp.setFillColor(sf::Color::Red);
        slots.push_back(temp);
    }
}

void Equipment::changeSlot(unsigned slot)
{
    selectedSlot=slot;
}

void Equipment::checkRecipes(vector<sf::Texture*>& v)
{
    int branches=0;
    int rocks=0;
    int logs=0;
    int planks=0;
    for(auto& i:crafting)
    {
        if(i->id==ITEMS::BRANCH) branches++;
        if(i->id==ITEMS::ROCK) rocks++;
        if(i->id==ITEMS::LOG) logs++;
        if(i->id==ITEMS::PLANKS) planks++;
    }

    if(branches==1&&rocks==1&&crafting.size()==2)
    {
        Item* temp = new Item(ITEMS::AXE);
        temp->setTexture(*v[6]);
        itemFromCrafting=temp;
        itemFromCrafting->setScale(0.65,0.65);
        itemFromCrafting->setPosition(slots[29].getPosition()-sf::Vector2f(3,3));
    }
    else if(branches==1&&rocks==2&&crafting.size()==3)
    {
        Item* temp = new Item(ITEMS::PICKAXE);
        temp->setTexture(*v[8]);
        itemFromCrafting=temp;
        itemFromCrafting->setScale(0.65,0.65);
        itemFromCrafting->setPosition(slots[29].getPosition()-sf::Vector2f(3,3));
    }
    else if(planks==4&&crafting.size()==4)
    {
        Item* temp = new Item(ITEMS::WOODENWALLITEM);
        temp->setTexture(*v[9]);
        itemFromCrafting=temp;
        itemFromCrafting->setScale(0.65,0.65);
        itemFromCrafting->setPosition(slots[29].getPosition()-sf::Vector2f(3,3));
    }
    else if(logs==1&&crafting.size()==1)
    {
        Item* temp = new Item(ITEMS::PLANKS);
        temp->setTexture(*v[7]);
        itemFromCrafting=temp;
        itemFromCrafting->setScale(0.65,0.65);
        itemFromCrafting->setPosition(slots[29].getPosition()-sf::Vector2f(3,3));
    }
    else
    {
        delete itemFromCrafting;
        itemFromCrafting=nullptr;
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
