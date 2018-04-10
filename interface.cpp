#include "interface.h"

PopUp::PopUp(sf::Texture* t)
{
    setScale(2,2);
}

void PopUp::update()
{
    desiredPos=sf::Vector2f(base.x,base.y-40-offset2);
    if(desiredPos.y<getPosition().y)
    {
        offset++;
    }
    counter-=0.2;
    setColor(sf::Color(255,255,255,counter));
    item.setColor(sf::Color(255,255,255,counter));
}

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

Interface::Interface(TextureLoader* tLoader)
{
    txtLoader=tLoader;
    font.loadFromFile("resources/fonts/sub.ttf");

    cursor.setTexture(*txtLoader->getCursorTexture());

    gTime.setFont(font);
    gTime.setCharacterSize(45);
    gTime.setColor(sf::Color(222, 191, 94));
    gTime.setOutlineColor(sf::Color(103, 87, 25));
    gTime.setOutlineThickness(4);
    gTime.setString("6:00");
}

void Interface::setTime(int t)
{
    gTime.setString(std::to_string(t)+":00");
}

void Interface::update(Player& p,sf::RenderWindow& window)
{
    fps.update();
    p.hpBar.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2+window.getView().getSize().x/40,
                        window.getView().getCenter().y-window.getView().getSize().y/2+window.getView().getSize().y/20);
    p.hpBar.setScale(window.getView().getSize().x/window.getSize().x*5,
                     window.getView().getSize().y/window.getSize().y*5);
    p.hungerBar.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2+window.getView().getSize().x/40,
                            window.getView().getCenter().y-window.getView().getSize().y/2+window.getView().getSize().y/10);
    p.hungerBar.setScale(window.getView().getSize().x/window.getSize().x*5,
                         window.getView().getSize().y/window.getSize().y*5);
    p.thirstBar.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2+window.getView().getSize().x/40,
                            window.getView().getCenter().y-window.getView().getSize().y/2+window.getView().getSize().y/6.7);
    p.thirstBar.setScale(window.getView().getSize().x/window.getSize().x*5,
                         window.getView().getSize().y/window.getSize().y*5);
    p.hpCover.setPosition(p.hpBar.getPosition()+sf::Vector2f(33,5));
    p.hungerCover.setPosition(p.hungerBar.getPosition()+sf::Vector2f(33,5));
    p.thirstCover.setPosition(p.thirstBar.getPosition()+sf::Vector2f(33,5));
    fps.fps.setPosition(window.getView().getCenter().x-window.getView().getSize().x/2,
                        window.getView().getCenter().y-window.getView().getSize().y/2);
    fps.fps.setScale(window.getView().getSize().x/window.getSize().x,
                     window.getView().getSize().y/window.getSize().y);
    gTime.setPosition(window.getView().getCenter().x-gTime.getGlobalBounds().width/2,
                      window.getView().getCenter().y-window.getView().getSize().y/2);
    gTime.setScale(window.getView().getSize().x/window.getSize().x,
                   window.getView().getSize().y/window.getSize().y);
    p.eq.setScale(window.getView().getSize().x/window.getSize().x*5,
                  window.getView().getSize().y/window.getSize().y*5);
    p.eq.setPosition(window.getView().getCenter().x-p.eq.getGlobalBounds().width/2.f,
                     window.getView().getCenter().y-p.eq.getGlobalBounds().height/2.f);
    sf::View temp = window.getView();
    cursor.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window),window.getView()));
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
    for(int i=popUps.size()-1; i>=0; i--)
    {
        if(popUps[i].counter<=0)
            popUps.erase(popUps.begin()+i);
        else
        {
            popUps[i].base=sf::Vector2f(window.getView().getCenter().x+400,window.getView().getCenter().y+270);
            popUps[i].setPosition(window.getView().getCenter().x+400,window.getView().getCenter().y+270-popUps[i].offset);
            popUps[i].item.setPosition(window.getView().getCenter().x+408,window.getView().getCenter().y+275-popUps[i].offset);
            popUps[i].update();
        }
    }
}

void Interface::popUp(int id)
{
    for(auto& pp:popUps)
    {
        pp.offset2+=40;
    }
    popUps.push_back(PopUp(txtLoader->items[id]));
    popUps.back().setTexture(*txtLoader->getPopUpTexture());
    popUps.back().item.setTexture(*txtLoader->getItemTexture(id));
    popUps.back().item.setScale(0.60,0.60);
}

void Interface::draw(Player& p,sf::RenderWindow& window)
{
    window.draw(p.hpBar);
    window.draw(p.hungerBar);
    window.draw(p.thirstBar);
    window.draw(p.hpCover);
    window.draw(p.hungerCover);
    window.draw(p.thirstCover);

    window.draw(fps.fps);
    if(p.eq.on)
    {
        window.draw(p.eq);
        for(auto& i:p.eq.items)
        {
            window.draw(*i);
        }
    }
    window.draw(gTime);
    for(auto& p:popUps)
    {
        window.draw(p);
        window.draw(p.item);
    }
    window.draw(cursor);
}


