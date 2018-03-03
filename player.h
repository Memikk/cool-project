#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "globals.h"
#include <math.h>
#include <iostream>
using namespace std;

class Player : public sf::Sprite
{
    sf::RectangleShape background;
    sf::Vector2f desiredPos;
public:
    bool animating=false;
    Player();
    sf::RectangleShape& getBackground(){return background;};
    void draw(sf::RenderWindow& window);
    void update(vector<bool> collisions);
    void moving(vector<bool> collisions);
    void animate();
};

#endif // PLAYER_H_INCLUDED
