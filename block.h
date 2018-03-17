#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"
#include <vector>
using namespace std;

enum blockType {NOBLOCK,GRASS,SAND,DIRT};
enum objectType {NOTHING,TREE,STONE,PLANT,WATER};
class Object : public sf::Sprite
{
public:
    int column; // kolumna tekstury
    objectType type=NOTHING;
    Object() {};
    virtual void animate(){};
    objectType getType()
    {
        return type;
    };
};

class Tree : public Object
{
public:
    Tree():Object()
    {
        type=TREE;
    };
};

class Stone : public Object
{
public:
    Stone():Object()
    {
        type=STONE;
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

class Block : public sf::RectangleShape
{
public:
    vector<Block*> collisions;
    Object* object=nullptr;
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
    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(*this);
        if(object!=nullptr)
            window.draw(*object);
    };
    blockType getType()
    {
        return type;
    };
};

class Grass : public Block
{
public:
    Grass();
    Grass(const Grass& g);
    ~Grass() {};
    void animate() {};
    void draw(sf::RenderWindow& window)
    {
        window.draw(*this);
        if(object!=nullptr)
            window.draw(*object);
    };
};

class Sand : public Block
{
public:
    Sand();
    ~Sand() {};
    void animate() {};
};

class Dirt : public Block
{
public:
    Dirt();
    ~Dirt() {};
    void animate() {};
};


#endif // BLOCK_H_INCLUDED
