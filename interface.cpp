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

    days.setFont(font);
    days.setCharacterSize(36);
    days.setScale(0.5,0.5);
    days.setColor(sf::Color(222, 191, 94));
    days.setOutlineColor(sf::Color(103, 87, 25));
    days.setOutlineThickness(4);
    days.setString("Day 1");
}

void Interface::setTime(int t)
{
    gTime.setString(std::to_string(t)+":00");
}

void Interface::setDays(int d)
{
    days.setString("Day "+std::to_string(d));
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
    p.hpCover.setPosition(p.hpBar.getPosition()+sf::Vector2f(window.getSize().x/60u,window.getSize().y/200u));
    p.hungerCover.setPosition(p.hungerBar.getPosition()+sf::Vector2f(window.getSize().x/60u,window.getSize().y/200u));
    p.thirstCover.setPosition(p.thirstBar.getPosition()+sf::Vector2f(window.getSize().x/60u,window.getSize().y/200u));
    p.hpCover.setScale(window.getView().getSize().x/window.getSize().x*2,
                       window.getView().getSize().y/window.getSize().y*2);
    p.hungerCover.setScale(window.getView().getSize().x/window.getSize().x*2,
                           window.getView().getSize().y/window.getSize().y*2);
    p.thirstCover.setScale(window.getView().getSize().x/window.getSize().x*2,
                           window.getView().getSize().y/window.getSize().y*2);

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

    cursor.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window),window.getView()));

    days.setPosition(window.getView().getCenter().x-days.getGlobalBounds().width/2,
                     window.getView().getCenter().y-window.getView().getSize().y/2.2);

    p.eq.itemsBar.setScale(window.getView().getSize().x/window.getSize().x*5,
                           window.getView().getSize().y/window.getSize().y*5);
    p.eq.itemsBar.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getView().getSize().x-
                              vh::getSize(p.eq.itemsBar).x,
                              2*window.getView().getSize().y-
                              vh::getSize(p.eq.itemsBar).y*2.5),
                              window.getView()));

//******************************************************************
//SLOTY W EQ
//******************************************************************
    for(int i=0; i<20; i++)
    {
        p.eq.slots[i].setPosition(window.mapPixelToCoords(sf::Vector2i(943+i%5*65,417+(i/5*65)),
                                  window.getView()));
    }
    for(int i=20; i<25; i++)
    {
        p.eq.slots[i].setPosition(window.mapPixelToCoords(sf::Vector2i(805+i%5*65,739+(i/5*65)),
                                  window.getView()));
    }
    for(int i=25; i<29; i++)
    {
        p.eq.slots[i].setPosition(window.mapPixelToCoords(sf::Vector2i(633+(i-25)%2*65,482+((i-25)/2*65)),
                                  window.getView()));
    }
    p.eq.slots[29].setPosition(window.mapPixelToCoords(sf::Vector2i(853,513),
                                  window.getView()));

//******************************************************************
//OBRAMOWANIE WYBRANEGO ITEMU

    p.eq.itemFrame.setScale(window.getView().getSize().x/window.getSize().x*3.8,
                           window.getView().getSize().y/window.getSize().y*3.8);
    p.eq.itemFrame.setPosition(p.eq.slots[p.eq.selectedSlot+20].getPosition()-sf::Vector2f(6.8,6.8));

//******************************************************************

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

    //RYSOWANIE ITEMOW NA PASKU SZYBKIEGO WYBORU
    for(int i=0; i<p.eq.bar.size(); i++)
    {
        p.eq.bar[i]->setScale(window.getView().getSize().x/window.getSize().x*1.3,
                                    window.getView().getSize().y/window.getSize().y*1.3);
        p.eq.bar[i]->setPosition(p.eq.slots[i+20].getPosition()-sf::Vector2f(4,4));
    }
    //******************************************

    //RYSOWANIE ITEMOW W OKNIE CRAFTINGU
    for(int i=0; i<p.eq.crafting.size(); i++)
    {
        p.eq.crafting[i]->setScale(window.getView().getSize().x/window.getSize().x*1.3,
                                    window.getView().getSize().y/window.getSize().y*1.3);
        p.eq.crafting[i]->setPosition(p.eq.slots[i+25].getPosition()-sf::Vector2f(4,4));
    }
    if(p.eq.itemFromCrafting) p.eq.itemFromCrafting->setPosition(p.eq.slots[29].getPosition()-sf::Vector2f(4,4));
    //******************************************
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

void Interface::popUp(int id,bool drop)
{
    for(auto& pp:popUps)
    {
        pp.offset2+=40;
    }
    popUps.push_back(PopUp(txtLoader->items[id]));
    if(drop)
        popUps.back().setTexture(*txtLoader->getPopUpDropTexture());
    else
        popUps.back().setTexture(*txtLoader->getPopUpPickTexture());
    popUps.back().item.setTexture(*txtLoader->getItemTexture(id));
    popUps.back().item.setScale(0.60,0.60);
}

void Interface::draw(Player& p,sf::RenderWindow& window)
{
    if(p.eq.bar.size()&&p.eq.bar.size()>p.eq.selectedSlot&&p.eq.bar[p.eq.selectedSlot]->building&&p.eq.buildingDrawingTexture)
    {
        buildingDrawing.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition()));
        buildingDrawing.setTexture(*p.eq.buildingDrawingTexture);
        window.draw(buildingDrawing);
    }

    window.draw(p.hpBar);
    window.draw(p.hungerBar);
    window.draw(p.thirstBar);
    window.draw(p.eq.itemsBar);
    window.draw(p.eq.itemFrame);
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
        for(auto& i:p.eq.crafting)
        {
            window.draw(*i);
        }
        if(p.eq.itemFromCrafting) window.draw(*p.eq.itemFromCrafting);
    }

    for(auto& i:p.eq.bar)
    {
        window.draw(*i);
    }

    //RYSOWANIE SLOTOW - DEBUGGING
//    for(auto& i:p.eq.slots)
//    {
//        window.draw(i);
//    }
    //****************************

    if(p.eq.itemHolder!=nullptr)
        window.draw(*p.eq.itemHolder);
    window.draw(gTime);
    window.draw(days);
    for(auto& p:popUps)
    {
        window.draw(p);
        window.draw(p.item);
    }
    //window.draw(cursor);
}


