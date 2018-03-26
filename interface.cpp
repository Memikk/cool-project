#include "interface.h"

FPS::FPS()
{
    font.loadFromFile("resources/fonts/arial.ttf");
    fps.setFont(font);
    fps.setCharacterSize(14);
    fps.setFillColor(sf::Color(255,200,50));
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(2);
}

void FPS::countFPS()
{
    if(fpsClock.getElapsedTime().asSeconds() >= 1.f)
    {
        mFps=mFrame;
        mFrame=0;
        fpsClock.restart();
    }
    mFrame++;
}

void FPS::update()
{
    fps.setString("FPS="+std::to_string(mFps));
    countFPS();
}

void Interface::update()
{
    fps.update();
}

void Interface::draw(Player& p,sf::RenderWindow& window)
{
    p.hpBar.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2+window.getView().getSize().x/40,
                        window.getView().getCenter().y-window.getView().getSize().y/2+window.getView().getSize().y/20);
    p.hpBar.setScale(window.getView().getSize().x/window.getSize().x*5,
                     window.getView().getSize().y/window.getSize().y*5);
    fps.fps.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2,
                        window.getView().getCenter().y-window.getView().getSize().y/2);
    fps.fps.setScale(window.getView().getSize().x/window.getSize().x,
                     window.getView().getSize().y/window.getSize().y);

    window.draw(p.hpBar);
    window.draw(fps.fps);
}
