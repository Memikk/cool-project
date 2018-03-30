#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "globals.h"
#include "equipment.h"
#include <math.h>
#include <iostream>

using namespace std;

class Player : public sf::Sprite
{
    int hp=100;
    sf::RectangleShape background;
    sf::Vector2f vel,acc;
    direction dir=DOWN;
public:
    Equipment eq;
    sf::Sprite hpBar;
    int ci,cj;
    sf::Vector2f centerOfBlock;
    bool animating=false;
    Player();
    sf::RectangleShape& getBackground(){return background;};
    void draw(sf::RenderWindow& window);
    void update(vector<Block*>& collisions);
    void moving(vector<Block*>& collisions);
    void animate(vector<Block*>& collisions);
    void changeTextureRect(int value);
};

#endif // PLAYER_H_INCLUDED
