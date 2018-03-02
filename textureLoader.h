#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED
#include <iostream>
using namespace std;

class TextureLoader
{
    vector<sf::Texture> txtPlayer;
public:
    TextureLoader(){};
    void load()
    {
        sf::Texture temp;
        temp.loadFromFile("player.png");
        txtPlayer.push_back(temp);
    }
    void initialize(Player& player)
    {
        player.setTexture(txtPlayer.back(),true);
        player.setScale(50/32.0,50/32.0);
    }
};

#endif // TEXTURELOADER_H_INCLUDED
