#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"

enum blockType{NOBLOCK,GRASS,SAND,WATER,DIRT};
enum objectType{NOTHING,TREE,STONE,PLANT};
class Object : public sf::Sprite
{
    public:
    objectType type=NOTHING;
    Object(){};
    objectType getType(){return type;};
};

class Tree : public Object
{
    public:
    Tree():Object(){type=TREE;};
};

class Stone : public Object
{
    public:
    Stone():Object(){type=STONE;};
};

class Block : public sf::RectangleShape
{
public:
    Object* object=nullptr;
    int i,j;
    float offsetX,offsetY;
    blockType t=NOBLOCK;
    int type; // kolumna tekstury
    bool collision=false;
    bool base=true;
    Block();
    Block(const Block& b);
    Block(sf::Vector2f pos);
    virtual ~Block(){};
    virtual void animate()=0;
    void draw(sf::RenderWindow& window){window.draw(*this);if(object!=nullptr)window.draw(*object);};
    blockType getType(){return t;};
};

class Grass : public Block
{
public:
    Grass();
    Grass(const Grass& g);
    ~Grass(){};
    void animate(){};
};

class Water : public Block
{
    int frame=0;
public:
    Water();
    ~Water(){};
    void animate();
    void nextFrame();
};

class Sand : public Block
{
public:
    Sand();
    ~Sand(){};
    void animate(){};
};

class Dirt : public Block
{
public:
    Dirt();
    ~Dirt(){};
    void animate(){};
};


#endif // BLOCK_H_INCLUDED
