#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"
#include "equipment.h"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Item;
enum blockType {NOBLOCK,DIRT,WATERB};
enum objectType {NOTHING,TREE,STONE,PLANT,WATER,SAND,GRASS,BUSH,BERRYBUSH,WHEAT,CARROT,WOODENFLOOR,WOODENWALL,STONEWALL,STONEFLOOR,ANIMATEDPLANT};
class Object : public sf::Sprite
{
    sf::Vector2f startPosition;
    sf::Vector2f comeback;
    queue<sf::Vector2f> shakePos;
public:
    int hp=4;
    int dropID=-1;
    bool side=true;
    bool destructable=false;
    int column; // kolumna tekstury
    objectType type=NOTHING;
    Object() {};
    virtual void animate(){};
    void shake();
    void update();
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
        hp=2;
        type=BUSH;
    };
};

class BerryBush : public Object
{
public:
    bool fruit=true;
    BerryBush():Object()
    {
        type=BERRYBUSH;
    };
};

class Stone : public Object
{
public:
    Stone():Object()
    {
        hp=5;
        type=STONE;
        destructable=true;
        dropID=1;
    };
};

class Water : public Object
{
    int counter=0;
    int frame=0;
public:
    Water():Object()
    {
        type=WATER;
    }
    void animate();
    void nextFrame();
};

class AnimatedPlant : public Object
{
    int counter=0;
    int frame=0;
public:
    AnimatedPlant():Object()
    {
        type=ANIMATEDPLANT;
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

class WoodenFloor : public Object
{
    public:
    WoodenFloor():Object()
    {
        type=WOODENFLOOR;
    };
};

class WoodenWall : public Object
{
    public:
    WoodenWall():Object()
    {
        type=WOODENWALL;
    };
};

class Block : public sf::RectangleShape
{
public:
    vector<Block*> collisions;
    bool side=true;
    Object* decoration=nullptr;
    Object* object=nullptr;
    Object* grass=nullptr;
    Object* cover=nullptr;
    vector<Item*> items;
    int i,j;
    float offsetX,offsetY;
    blockType type=NOBLOCK;
    int column=0; // kolumna tekstury
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
