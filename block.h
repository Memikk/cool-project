#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"
#include "equipment.h"
#include <vector>
#include <iostream>
using namespace std;

class Item;
enum blockType {NOBLOCK,DIRT};
enum objectType {NOTHING,TREE,STONE,PLANT,WATER,SAND,GRASS,BUSH,WHEAT,CARROT};
class Object : public sf::Sprite
{
public:
    int dropID=-1;
    bool side=true;
    bool destructable=false;
    int column; // kolumna tekstury
    objectType type=NOTHING;
    Object() {};
    virtual void animate(){};
    objectType getType()
    {
        return type;
    };
};

class Grass : public Object
{
public:
    Grass():Object()
    {
        type=GRASS;
    };
};

class Tree : public Object
{
public:
    Tree():Object()
    {
        type=TREE;
        destructable=true;
        dropID=5;
    };
};

class Bush : public Object
{
public:
    Bush():Object()
    {
        type=BUSH;
    };
};

class Stone : public Object
{
public:
    Stone():Object()
    {
        type=STONE;
        destructable=true;
        dropID=1;
    };
};

class Water : public Object
{
    int frame=0;
public:
    Water():Object()
    {
        type=WATER;
    }
    void animate();
    void nextFrame();
};

class Sand : public Object
{
    public:
    Sand():Object()
    {
        type=SAND;
    };
};

class Wheat : public Object
{
    public:
    Wheat():Object()
    {
        type=WHEAT;
    };
};

class Carrot : public Object
{
    public:
    Carrot():Object()
    {
        type=CARROT;
    };
};

class Block : public sf::RectangleShape
{
public:
    vector<Block*> collisions;
    bool side=true;
    Object* object=nullptr;
    Object* grass=nullptr;
    Object* cover=nullptr;
    vector<Item*> items;
    int i,j;
    float offsetX,offsetY;
    blockType type=NOBLOCK;
    int column; // kolumna tekstury
    bool collision=false;
    bool base=true;
    Block();
    Block(const Block& b);
    Block(sf::Vector2f pos);
    virtual ~Block() {};
    virtual void animate()=0;
    virtual void draw(sf::RenderWindow& window);
    blockType getType()
    {
        return type;
    };
};

class Dirt : public Block
{
public:
    Dirt();
    ~Dirt() {};
    void animate() {};
};


#endif // BLOCK_H_INCLUDED
