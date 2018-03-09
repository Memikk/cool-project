#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "globals.h"
#include "block.h"
#include <math.h>
#include <iostream>
using namespace std;

class Player : public sf::Sprite
{
    sf::RectangleShape background;
    sf::FloatRect hitbox;
    sf::Vector2f vel,acc;
public:
    bool animating=false;
    Player();
    sf::RectangleShape& getBackground(){return background;};
    void draw(sf::RenderWindow& window);
    void update(vector<Block*>& collisions);
    void moving();
    void animate(vector<Block*>& collisions);
};

#endif // PLAYER_H_INCLUDED
