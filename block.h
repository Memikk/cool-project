#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "globals.h"

class Block : public sf::RectangleShape
{
public:
    bool collision=false;
    bool base=true;
    Block();
    Block(const Block& b);
    Block(sf::Vector2f pos);
    virtual void setObjectTexture(sf::Texture& t,int offset=0){};
    virtual void initialize()=0;
    virtual void animate()=0;
    virtual void draw(sf::RenderWindow& window);
};

class Grass : public Block
{
    bool tree=false;
    bool plant=false;
public:
    sf::Sprite object;
    Grass(bool tree=false,bool plant=false);
    Grass(const Grass& g);
    void setObjectTexture(sf::Texture& t,int offset=0);
    void initialize();
    void animate(){};
    void draw(sf::RenderWindow& window);
};

class Water : public Block
{
    int frame=0;
public:
    Water();
    void initialize(){};
    void animate();
    void nextFrame();
};

class Sand : public Block
{
public:
    Sand();
    void initialize(){};
    void animate(){};
};

class Stone : public Block
{
public:
    Stone();
    void initialize(){};
    void animate(){};
};


#endif // BLOCK_H_INCLUDED
