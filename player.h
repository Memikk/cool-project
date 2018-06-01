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
public:
    direction dir=DOWN;
    int hp=100;
    int hunger=100;
    int thirst=100;
    int counter=0;
    int aniCounter=0;

    Equipment eq;

    sf::Sprite hpBar;
    sf::Sprite hungerBar;
    sf::Sprite thirstBar;
    sf::RectangleShape hpCover;
    sf::RectangleShape hungerCover;
    sf::RectangleShape thirstCover;

    int ci,cj;
    sf::Vector2f centerOfBlock;
    bool animating=false;
    Player();
    sf::RectangleShape& getBackground(){return background;};
    void draw(sf::RenderWindow& window);
    void update(vector<Block*>& collisions);
    void moving(vector<Block*>& collisions);
    void animate(vector<Block*>& collisions);
    void changeTextureRect(int value,int value2);
};

#endif // PLAYER_H_INCLUDED
