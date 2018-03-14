#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "globals.h"
#include <math.h>
#include <iostream>

using namespace std;

class Player : public sf::Sprite
{
    sf::RectangleShape background;
    sf::Vector2f vel,acc;
    direction dir=DOWN;
    TextureLoader* txtLoader;
public:
    int ci,cj;
    sf::Vector2f centerOfBlock;
    bool animating=false;
    Player();
    sf::RectangleShape& getBackground(){return background;};
    void draw(sf::RenderWindow& window);
    void update(vector<Block*>& collisions);
    void moving(vector<Block*>& collisions);
    void animate(vector<Block*>& collisions);
    void mine(vector<Block*>& cllisions);
};

#endif // PLAYER_H_INCLUDED
