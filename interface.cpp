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

void Interface::update(Player& p,sf::RenderWindow& window)
{
    fps.update();
    p.hpBar.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2+window.getView().getSize().x/40,
                        window.getView().getCenter().y-window.getView().getSize().y/2+window.getView().getSize().y/20);
    p.hpBar.setScale(window.getView().getSize().x/window.getSize().x*5,
                     window.getView().getSize().y/window.getSize().y*5);
    fps.fps.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2,
                        window.getView().getCenter().y-window.getView().getSize().y/2);
    fps.fps.setScale(window.getView().getSize().x/window.getSize().x,
                     window.getView().getSize().y/window.getSize().y);
    p.eq.setScale(window.getView().getSize().x/window.getSize().x*5,
                  window.getView().getSize().y/window.getSize().y*5);
    p.eq.setPosition(window.getView().getCenter().x-p.eq.getGlobalBounds().width/2.f,
                     window.getView().getCenter().y-p.eq.getGlobalBounds().height/2.f);
    if(p.eq.on)
    {
        for(int i=0; i<p.eq.items.size(); i++)
        {
            int xo=i%5;
            int yo=i/5;

            p.eq.items[i]->setScale(window.getView().getSize().x/window.getSize().x*1.3,
                                    window.getView().getSize().y/window.getSize().y*1.3);
            p.eq.items[i]->setPosition(window.getView().getCenter().x-p.eq.getGlobalBounds().width/2.f+
                                       window.getView().getSize().x/BLOCK_SIZE*(xo*1.7)+
                                       window.getView().getSize().x/5.1,
                                       window.getView().getCenter().y-p.eq.getGlobalBounds().height/2.f+
                                       window.getView().getSize().y/11.8+
                                       window.getView().getSize().y/16.4*yo);
        }
    }
}

void Interface::draw(Player& p,sf::RenderWindow& window)
{

    window.draw(p.hpBar);
    window.draw(fps.fps);
    if(p.eq.on)
    {
        window.draw(p.eq);
        for(auto& i:p.eq.items)
        {
            window.draw(*i);
        }
    }
}


