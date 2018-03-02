#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "globals.h"
#include <math.h>
#include <iostream>
using namespace std;

class Player : public sf::Sprite
{
    bool animating=false;
    sf::RectangleShape background;
    sf::Vector2f desiredPos;
public:
    Player();
    sf::RectangleShape& getBackground(){return background;};
    void draw(sf::RenderWindow& window);
    void update();
    void moving();
    void animate();
};

#endif // PLAYER_H_INCLUDED
