#include "world.h"

Chunk::Chunk(int offX,int offY,siv::PerlinNoise& perlin,TextureLoader* txtLoader):ix(offX),iy(offY),offsetX(offX*CHUNK_SIZE*BLOCK_SIZE),offsetY(offY*CHUNK_SIZE*BLOCK_SIZE)
{

    blocks = new Block** [CHUNK_SIZE];
    for(int i=0; i<CHUNK_SIZE; i++)
    {
        blocks[i] = new Block* [CHUNK_SIZE];
        for(int j=0; j<CHUNK_SIZE; j++)
        {
            blocks[i][j] = nullptr;
            int xp=offsetX+i*BLOCK_SIZE;
            int yp=offsetY+j*BLOCK_SIZE;

            float choice=worldGenNoise.noise0_1((float)xp*0.002,(float)yp*0.002);
            float choice1=worldGenNoise.noise0_1((float)xp*0.0001,(float)yp*0.0001);
            float choice2=objectNoise.noise0_1((float)xp*0.002,(float)yp*0.002);
            float choice3=objectNoise2.noise0_1((float)xp*0.002,(float)yp*0.002);

            blocks[i][j] = new Dirt();
            blocks[i][j] -> i = i;
            blocks[i][j] -> j = j;
            txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,DIRT,0.0);

            if(choice>0.30)
            {
                blocks[i][j]->grass = new Grass();
                txtLoader->chooseTexture(*blocks[i][j]->grass,i,j,offsetX,offsetY,GRASS,0.30,worldGenNoise);
                if(choice<0.5&&choice1<0.50)
                {
                    txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,WATERB,0.0);
                }

            }
            if(choice<=0.30&&choice1<0.50)
            {
                blocks[i][j]->object = new Water();
                blocks[i][j]->collision = true;
                txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,WATER,0,worldGenNoise);
            }


            if(blocks[i][j]->object==nullptr||blocks[i][j]->object->type==objectType::WATER)
            {
                if(choice>0.75)
                {
                    blocks[i][j]->object = new Stone();
                    blocks[i][j]->collision=true;
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,STONE,0.75,worldGenNoise);
                }
            }
            if(blocks[i][j]->object==nullptr)
            {
                if((choice2<0.50||(choice2>=0.35&&(int)(choice2*234)%25==0))&&choice3<=0.69)
                {
                    if((int)(choice2*100)%3)
                    {
                        blocks[i][j]->object = new Tree();
                        blocks[i][j]->collision=true;
                        txtLoader->setTreeTexture(*blocks[i][j]->object);
                        int tmp = (int)(choice1*choice2*choice3*2359)%6;
                        blocks[i][j]->object->setTextureRect(sf::IntRect(0,50*tmp,50,50));
                    }
                    else if((int)(choice2*10)%2)
                    {
                        if((int)(choice1*100)%10)
                        {
                            blocks[i][j]->object = new Bush();
                            blocks[i][j]->collision=true;
                            txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,BUSH,0,objectNoise);
                        }
                        else
                        {
                            blocks[i][j]->object = new BerryBush();
                            blocks[i][j]->collision=true;
                            txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,BERRYBUSH,0,objectNoise);
                        }
                    }
                }
                else if(((choice3<0.25&&(int)(choice3*100)%3)||(choice3>=0.25&&(int)(choice3*187)%37==0))&&choice3<=0.64)
                {
                    blocks[i][j]->object = new Bush();
                    blocks[i][j]->collision=true;
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,BUSH,0,objectNoise);
                }
                else if(((choice3<0.30&&(int)(choice3*500)%189==0)||(choice3>=0.30&&(int)(choice3*188)%79==0))&&choice3<=0.64)
                {
                    blocks[i][j]->object = new Wheat();
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,WHEAT,0,objectNoise);
                }
                else if(((choice3<0.60&&(int)(choice3*500)%116==0)||(choice3>=0.50&&(int)(choice3*132)%26==0))&&choice3<=0.64)
                {
                    blocks[i][j]->object = new Carrot();
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,CARROT,0,objectNoise);
                }
            }

            if(blocks[i][j]->object==nullptr)
            {
                int c = rand()%50;
                if(c==0)
                {
                    blocks[i][j]->items.push_back(new Item(ITEMS::BRANCH));
                    txtLoader->setItemTexture(*blocks[i][j]->items.back(),0);
                }
                else if(c==1)
                {
                    blocks[i][j]->items.push_back(new Item(ITEMS::ROCK));
                    txtLoader->setItemTexture(*blocks[i][j]->items.back(),1);
                }
            }

            if(blocks[i][j]->object==nullptr)
            {
                if((int)(choice*choice2*223)%17==0)
                {
                    if((int)(choice*choice3*323)%8)
                    {
                        blocks[i][j]->decoration = new Object();
                        txtLoader->setDecorationTexture(*blocks[i][j]->decoration,(int)(choice2*choice3*543)%5);
                    }
                    else
                    {
                        blocks[i][j]->object = new AnimatedPlant();
                        txtLoader->setTexture(*blocks[i][j]->object,ANIMATEDPLANT,0);
                        blocks[i][j]->setTextureRect(sf::IntRect(0,0,50,50));
                    }
                }
            }

            blocks[i][j]->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->object!=nullptr)
                blocks[i][j]->object->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->grass!=nullptr)
                blocks[i][j]->grass->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->cover!=nullptr)
                blocks[i][j]->cover->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->decoration!=nullptr)
                blocks[i][j]->decoration->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->items.size()>0&&blocks[i][j]->items.back()!=nullptr)
                blocks[i][j]->items.back()->setPosition(sf::Vector2f(xp,yp));
        }
    }
}

bool Chunk::operator==(const Chunk& chunk)
{
    if(ix==chunk.ix&&iy==chunk.iy)
        return true;
    else
        return false;
}

Block& Chunk::randBlock(bool collision)
{
    Block* temp;
    do
    {
        temp=blocks[rand()%15][rand()%15];
    }
    while(temp->collision==true);
    return *temp;
}

void Chunk::draw(sf::RenderWindow& window)
{
    for(int i=0; i<CHUNK_SIZE; i++)
    {
        for(int j=0; j<CHUNK_SIZE; j++)
        {
            //if(i==0||j==0)
            //blocks[i][j]->setFillColor(sf::Color::Black);
            blocks[i][j]->draw(window);
            if(blocks[i][j]->object&&(blocks[i][j]->object->type==WATER||
                                      blocks[i][j]->object->type==ANIMATEDPLANT))
            {
                blocks[i][j]->object->animate();
            }
            blocks[i][j]->setFillColor(sf::Color::White);
            if(blocks[i][j]->object!=nullptr)
                blocks[i][j]->object->setColor(sf::Color::White);
            //if(blocks[i][j]->grass!=nullptr) blocks[i][j]->grass->setColor(sf::Color::White);
            if(blocks[i][j]->cover!=nullptr)
                blocks[i][j]->cover->setColor(sf::Color::White);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~WORLD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

World::World(TextureLoader* tloader,Interface* intface,Saver* s)
{
    saver=s;
    txtLoader=tloader;
    iface=intface;
    player.setPosition(0,0);

    player.eq.items.push_back(new Item(ITEMS::WOODENWALLITEM));
    player.eq.items.back()->building=true;
    txtLoader->setItemTexture(*player.eq.items.back(),9);

    player.eq.items.push_back(new Item(ITEMS::PICKAXE));
    player.eq.items.back()->tool=true;
    txtLoader->setItemTexture(*player.eq.items.back(),8);

    player.eq.items.push_back(new Item(ITEMS::AXE));
    player.eq.items.back()->tool=true;
    txtLoader->setItemTexture(*player.eq.items.back(),6);

    daynight.setFillColor(sf::Color(0,0,0,0));
    daynight.setSize(sf::Vector2f(1920,1080));
}

void World::start(sf::RenderWindow* window,sf::View* view)
{
    view->setCenter(getPlayer().getPosition().x+BLOCK_SIZE/2,getPlayer().getPosition().y+BLOCK_SIZE/2);
    view->setSize(sf::Vector2f(window->getSize().x/2,window->getSize().y/2));
    window->setView(*view);
    cout<<"gra stworzona"<<endl;

    generateChunks();
    loadChunks();
}

void World::newStart(sf::RenderWindow* window,sf::View* view)
{
    view->setCenter(getPlayer().getPosition().x+BLOCK_SIZE/2,getPlayer().getPosition().y+BLOCK_SIZE/2);
    view->setSize(sf::Vector2f(window->getSize().x/2,window->getSize().y/2));
    window->setView(*view);
    cout<<"gra stworzona"<<endl;

    int s1=rand()*483232;
    int s2=rand()*535638;
    worldGenNoise.reseed(s1);
    objectNoise.reseed(s2);

    fstream s1s("save1seed.txt",std::ofstream::out | std::ofstream::trunc);
    cerr<<s1<<" "<<std::to_string(s1)<<endl;
    s1s<<std::to_string(s1)<<endl<<std::to_string(s2)<<endl;
    s1s.close();

    fstream cleaningChunks("save1.txt",std::ofstream::out | std::ofstream::trunc);
    cleaningChunks.close();

    fstream cleaningPlayer("save1player.txt",std::ofstream::out | std::ofstream::trunc);
    cleaningPlayer.close();

    player.setPosition(0,0);

    generateChunks();
}

void World::loadChunks()
{
    fstream save("save1.txt",ios::in);
    string line;

    while(getline(save,line))
    {
        line.erase(line.begin());
        stringstream ss(line);
        int i,j;
        ss>>i;
        ss>>j;

        if(exist(i,j))
        {
            Chunk* temp = getChunk(i,j);

            getline(save,line);
            line.erase(line.begin());
            ss=stringstream(line);
            ss>>i;
            ss>>j;

            getline(save,line);
            if(line[1]=='o')
            {

                temp->blocks[i][j]->object = new Object();
                temp->blocks[i][j]->object->setPosition(temp->blocks[i][j]->getPosition());
                txtLoader->setTexture(*temp->blocks[i][j]->object,WOODENWALL,0);
                temp->blocks[i][j]->collision=true;
            }
            else if(line[1]=='f')
            {

                temp->blocks[i][j]->object = new Object();
                temp->blocks[i][j]->object->setPosition(temp->blocks[i][j]->getPosition());
                txtLoader->setTexture(*temp->blocks[i][j]->object,WOODENFLOOR,0);
                temp->blocks[i][j]->collision=false;
            }
            else if(line[1]=='u')
            {

                temp->blocks[i][j]->object = new Object();
                temp->blocks[i][j]->object->setPosition(temp->blocks[i][j]->getPosition());
                txtLoader->setTexture(*temp->blocks[i][j]->object,STONEWALL,0);
                temp->blocks[i][j]->collision=true;
            }
            else if(line[1]=='i')
            {

                temp->blocks[i][j]->object = new Object();
                temp->blocks[i][j]->object->setPosition(temp->blocks[i][j]->getPosition());
                txtLoader->setTexture(*temp->blocks[i][j]->object,STONEFLOOR,0);
                temp->blocks[i][j]->collision=false;
            }
            else if(line[1]=='s')
            {

                temp->blocks[i][j]->object = new Object();
                temp->blocks[i][j]->object->setPosition(temp->blocks[i][j]->getPosition());
                txtLoader->setTexture(*temp->blocks[i][j]->object,STONE,0);
                temp->blocks[i][j]->collision=true;
            }
            else if(line[1]=='x')
            {
                temp->blocks[i][j]->collision=false;
                temp->blocks[i][j]->object = new Object();
                temp->blocks[i][j]->collision=false;
            }
        }
    }
}

void World::generateChunks()
{
    int offsetX;
    int offsetY;
    if(player.getPosition().x>=0)
        offsetX=player.getPosition().x/(CHUNK_SIZE*BLOCK_SIZE);
    else
        offsetX=floor(player.getPosition().x/(CHUNK_SIZE*BLOCK_SIZE));

    if(player.getPosition().y>=0)
        offsetY=player.getPosition().y/(CHUNK_SIZE*BLOCK_SIZE);
    else
        offsetY=floor(player.getPosition().y/(CHUNK_SIZE*BLOCK_SIZE));

    //std::thread popChunksThread(&World::popChunks,*this,offsetX,offsetY);

    player.ci=offsetX;
    player.cj=offsetY;

    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            if(!exist(offsetX+i,offsetY+j))
            {
                chunks.push_back(Chunk(offsetX+i,offsetY+j,perlin,txtLoader));
            }
        }
    }
    //popChunksThread.join();
}

void World::popChunks(int x,int y)
{
    for(int i=chunks.size()-1; i>=0; i--)
    {
        if(x+2<chunks[i].ix||x-2>chunks[i].ix)
            chunks.erase(chunks.begin()+i);
        if(y+2<chunks[i].iy||y-2>chunks[i].iy)
            chunks.erase(chunks.begin()+i);
    }
}

void World::updateEntities(const sf::View& view)
{
    for(auto& e:entities)
    {
        sf::FloatRect f(view.getCenter().x-view.getSize().x/2,view.getCenter().y-view.getSize().y/2,
                        view.getSize().x,view.getSize().y);
        if(f.contains(e->getPosition()))
        {
            if(e->type==WOLF)
            {
                static_cast<Wolf*>(e)->update(getCollisions(e->getPosition()),entities,player);
            }
            else
                e->update(getCollisions(e->getPosition()));
        }
    }
}

void World::update(sf::RenderWindow& window)
{
    //cout<<"TWORZENIE KOLIZJI"<<endl;
    std::thread ue(&World::updateEntities,*this,window.getView());

    //cout<<"PLAYER UPDATE"<<endl;
    vector<Block*> c=getCollisions(player.getPosition());
    player.update(c);

    daynight.setPosition(player.getPosition()-(sf::Vector2f)window.getSize()/2.f);
    if(dayClock.getElapsedTime().asSeconds()>=10.f)
    {
        dayClock.restart();
        gameTime++;
        if(gameTime>23)
        {
            gameTime=0;
            days++;
        }
        cout<<gameTime<<":00"<<endl;
    }
    if((gameTime>21||gameTime<3)&&dayCounter<140)
    {
        dayCounter+=0.1;
    }
    else if(gameTime<8&&dayCounter>0)
        dayCounter-=0.1;

    if(((gameTime>16&&gameTime<=21)||(gameTime>=3&&gameTime<8))&&redCounter<100)
        redCounter+=1;
    else if((gameTime>21||gameTime<3||gameTime>=8)&&redCounter>0)
        redCounter-=1;


    if(gameTime==8)
        dayCounter=0;
    daynight.setFillColor(sf::Color(0,0,0,dayCounter));

    if(player.eq.itemHolder!=nullptr)
    {
        player.eq.itemHolder->setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)-sf::Vector2i(25,25)));
    }

    Item* holdItem = nullptr;
    if(player.eq.bar.size()>player.eq.selectedSlot)
        holdItem=player.eq.bar[player.eq.selectedSlot];
    Block* temp = getBlock(window.mapPixelToCoords(sf::Mouse::getPosition()-sf::Vector2i(33,50)));
    if(holdItem&&holdItem->building)
    {
        if(temp)
        {
            if(temp->cover)
            {
                if(temp->collision)
                    temp->cover->setColor(sf::Color::Red);
                else
                    temp->cover->setColor(sf::Color(0,100,255));
            }
            if(temp->object)
            {
                if(temp->collision)
                    temp->object->setColor(sf::Color::Red);
                else
                    temp->object->setColor(sf::Color(0,100,255));
            }
            if(temp->grass)
            {
                if(temp->collision)
                    temp->grass->setColor(sf::Color::Red);
                else
                    temp->grass->setColor(sf::Color(0,100,255));
            }
            if(temp->collision)
                temp->setFillColor(sf::Color::Red);
            else
                temp->setFillColor(sf::Color(0,100,255));
        }
    }
    if(temp&&
            temp->object&&
            temp->object->type==objectType::BERRYBUSH&&
            static_cast<BerryBush*>(temp->object)->fruit&&
            vh::distance(temp->object->getPosition(),player.getPosition())<playerRange)
    {
        temp->object->setColor(sf::Color(0,100,255));
    }
    if(temp&&holdItem&&holdItem->tool&&vh::distance(player.getPosition(),temp->getPosition())<playerRange)
    {
        if(holdItem->id==ITEMS::AXE)
        {
            if(temp->object&&
                    (temp->object->type==objectType::TREE||
                     temp->object->type==objectType::BUSH||
                     temp->object->type==objectType::BERRYBUSH||
                     temp->object->type==objectType::WOODENWALL||
                     temp->object->type==objectType::WOODENFLOOR))
            {
                temp->object->setColor(sf::Color(0,100,255));
            }
        }
        if(holdItem->id==ITEMS::PICKAXE)
        {
            if(temp->object&&(temp->object->type==objectType::STONE||
                              temp->object->type==objectType::STONEWALL||
                              temp->object->type==objectType::STONEFLOOR))
            {
                temp->object->setColor(sf::Color(0,100,255));
            }
        }
    }

    ue.join();
}

sf::Vector2i World::blockID(sf::Vector2f chunk,sf::Vector2f pos)
{
    int ix,iy;
    int tx,ty;

    tx=chunk.x*CHUNK_SIZE*BLOCK_SIZE;
    ty=chunk.y*CHUNK_SIZE*BLOCK_SIZE;

    ix=abs((pos.x-tx)/BLOCK_SIZE);
    iy=abs((pos.y-ty)/BLOCK_SIZE);

    return sf::Vector2i(ix,iy);
}

Chunk& World::getChunkFromPos(sf::Vector2f pos)
{
    int ox,oy;
    if(pos.x>=0)
        ox=pos.x/(CHUNK_SIZE*BLOCK_SIZE);
    else
        ox=floor(pos.x/(CHUNK_SIZE*BLOCK_SIZE));

    if(pos.y>=0)
        oy=pos.y/(CHUNK_SIZE*BLOCK_SIZE);
    else
        oy=floor(pos.y/(CHUNK_SIZE*BLOCK_SIZE));

    return *getChunk(ox,oy);
}

Block* World::blockCollision(sf::Vector2f pos)
{
    int ox,oy;

    if(pos.x>=0)
        ox=pos.x/(CHUNK_SIZE*BLOCK_SIZE);
    else
        ox=floor(pos.x/(CHUNK_SIZE*BLOCK_SIZE));

    if(pos.y>=0)
        oy=pos.y/(CHUNK_SIZE*BLOCK_SIZE);
    else
        oy=floor(pos.y/(CHUNK_SIZE*BLOCK_SIZE));

    sf::Vector2i idx = blockID(sf::Vector2f(ox,oy),pos);
    return getChunk(ox,oy)->blocks[idx.x][idx.y];
}


vector<Block*> World::getCollisions(sf::Vector2f ppos)
{
    vector<Block*> collisions;
    ppos+=sf::Vector2f(12,16);
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x-BLOCK_SIZE,ppos.y-BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x,ppos.y-BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x+BLOCK_SIZE,ppos.y-BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x+BLOCK_SIZE,ppos.y)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x+BLOCK_SIZE,ppos.y+BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x,ppos.y+BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x-BLOCK_SIZE,ppos.y+BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x-BLOCK_SIZE,ppos.y)));

//    for(auto& c:collisions)
//    {
//        c->setFillColor(sf::Color::Red);
//        if(c->object!=nullptr)
//            c->object->setColor(sf::Color::Blue);
//        //if(c->grass!=nullptr) c->grass->setColor(sf::Color::Blue);
//    }

    return collisions;
}

bool World::exist(int x,int y) const
{
    for(auto c:chunks)
    {
        if(c.ix==x&&c.iy==y)
            return true;
    }
    return false;
}

Chunk* World::getChunk(int x,int y)
{
    for(auto &c:chunks)
    {
        if(c.ix==x&&c.iy==y)
            return &c;
    }
    return nullptr;
}

void World::pickUpItem()
{
    Item* item =nullptr;
    Block* b = nullptr;
    Chunk* c = nullptr;

    sf::Vector2i ids = blockID(sf::Vector2f(player.ci,player.cj),player.getPosition()+sf::Vector2f(15,25));

    c = getChunk(player.ci,player.cj);
    if(c!=nullptr&&ids.x>=0&&ids.x<16&&ids.x>=0&&ids.y<16)
        b = c->blocks[ids.x][ids.y];
    else
        return;
    if(b==nullptr)
        return;

    if(b->cover!=nullptr)
        b->cover->setColor(sf::Color::Cyan);

    if(b->items.size()>0)
        item = b->items.back();
    else if(b->object&&b->object->type==WHEAT)
    {
        item = new Item(ITEMS::WHEAT);
        txtLoader->setItemTexture(*item,3);
        b->object=nullptr;
        iface->popUp(3);
        player.eq.add(item);
        return;
    }
    else if(b->object&&b->object->type==CARROT)
    {
        item = new Item(ITEMS::CARROT);
        txtLoader->setItemTexture(*item,4);
        b->object=nullptr;
        iface->popUp(4);
        item->food=true;
        player.eq.add(item);
        return;
    }
    else
        return;
    if(item!=nullptr)
    {
        iface->popUp((int)b->items.back()->id);
        b->items.pop_back();
        player.eq.add(item);
    }

}

Block* World::getBlock(sf::Vector2f pos)
{
    int ox,oy;

    if(pos.x>=0)
        ox=pos.x/(CHUNK_SIZE*BLOCK_SIZE);
    else
        ox=floor(pos.x/(CHUNK_SIZE*BLOCK_SIZE));

    if(pos.y>=0)
        oy=pos.y/(CHUNK_SIZE*BLOCK_SIZE);
    else
        oy=floor(pos.y/(CHUNK_SIZE*BLOCK_SIZE));

    Chunk *c = nullptr;
    Block *b = nullptr;

    sf::Vector2i ids = blockID(sf::Vector2f(ox,oy),pos+sf::Vector2f(15,25));

    c = getChunk(ox,oy);
    if(c!=nullptr&&ids.x>=0&&ids.x<16&&ids.x>=0&&ids.y<16)
        b = c->blocks[ids.x][ids.y];
    if(b==nullptr)
        return nullptr;
    return b;
}

void World::dropItemOnGround(sf::Vector2f mpos)
{
    Chunk *c = nullptr;
    Block *b = nullptr;
    sf::Vector2i ids = blockID(sf::Vector2f(player.ci,player.cj),player.getPosition()+sf::Vector2f(15,25));

    c = getChunk(player.ci,player.cj);
    if(c!=nullptr&&ids.x>=0&&ids.x<16&&ids.x>=0&&ids.y<16)
        b = c->blocks[ids.x][ids.y];
    if(b==nullptr)
        return;
    for(int i=0; i<player.eq.items.size(); i++)
    {
        if(player.eq.items[i]->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            Item * temp = player.eq.items[i];
            iface->popUp((int)temp->id,true);
            player.eq.items.erase(player.eq.items.begin()+i);
            temp->setScale(10/6,10/6);
            temp->setPosition(b->getPosition());
            b->items.push_back(temp);
        }
    }
}

void World::takeItem(sf::Vector2f mpos)
{
    if(player.eq.itemFromCrafting!=nullptr&&player.eq.itemFromCrafting->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
    {
        player.eq.itemHolder = player.eq.itemFromCrafting;
        player.eq.itemFromCrafting=nullptr;
        for(int i=player.eq.crafting.size()-1; i>=0; i--)
        {
            delete player.eq.crafting[i];
            player.eq.crafting[i]=nullptr;
            player.eq.crafting.pop_back();
        }
        return;
    }
    for(int i=0; i<player.eq.items.size(); i++)
    {
        if(player.eq.items[i]->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            player.eq.itemHolder = player.eq.items[i];
            player.eq.items.erase(player.eq.items.begin()+i);
            return;
        }
    }
    for(int i=0; i<player.eq.bar.size(); i++)
    {
        if(player.eq.bar[i]->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            player.eq.itemHolder = player.eq.bar[i];
            player.eq.bar.erase(player.eq.bar.begin()+i);
            return;
        }
    }
    for(int i=0; i<player.eq.crafting.size(); i++)
    {
        if(player.eq.crafting[i]->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            player.eq.itemHolder = player.eq.crafting[i];
            player.eq.crafting.erase(player.eq.crafting.begin()+i);
            player.eq.checkRecipes(txtLoader->AllItems());
            return;
        }
    }
}

void World::dropItemInEq(sf::Vector2f mpos)
{
    if(player.eq.itemHolder==nullptr)
        return;

    for(int i=0; i<player.eq.slots.size(); i++)
    {
        if(player.eq.slots[i].getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            if(i>=25)
            {
                player.eq.crafting.push_back(player.eq.itemHolder);
                player.eq.checkRecipes(txtLoader->AllItems());
            }
            else if(i>=20&&i-20>player.eq.bar.size())
            {
                player.eq.bar.push_back(player.eq.itemHolder);
            }
            else if(i>=20)
            {
                player.eq.bar.insert(player.eq.bar.begin()+i-20,player.eq.itemHolder);
            }
            else if(i>player.eq.items.size())
            {
                player.eq.items.push_back(player.eq.itemHolder);
            }
            else if(player.eq.items.size()<20)
            {
                player.eq.items.insert(player.eq.items.begin()+i,player.eq.itemHolder);
            }
            else
            {
                player.eq.itemFromCrafting=player.eq.itemHolder;
            }
            player.eq.itemHolder=nullptr;
            return;
        }
    }
    player.eq.items.push_back(player.eq.itemHolder);
    player.eq.itemHolder=nullptr;
}

void World::eat()
{
    if(player.hunger<=90)
    {
        if(player.eq.bar[player.eq.selectedSlot]->food)
        {
            player.hunger+=10;
            player.hungerCover.setSize(sf::Vector2f(120-player.hunger*1.2,player.hungerCover.getSize().y));
            Item *temp = player.eq.bar[player.eq.selectedSlot];
            iface->popUp((int)temp->id,true);
            player.eq.bar.erase(player.eq.bar.begin()+player.eq.selectedSlot);
            delete temp;
        }
    }
}

void World::drink()
{
    if(player.thirst<=90)
    {
        vector<Block*> collisions = getCollisions(player.getPosition());
        if(collisions[1]!=nullptr&&collisions[3]!=nullptr&&collisions[5]!=nullptr&&collisions[7]!=nullptr)
        {
            if((collisions[1]->object&&collisions[1]->object->type==WATER)||
                    (collisions[3]->object&&collisions[3]->object->type==WATER)||
                    (collisions[5]->object&&collisions[5]->object->type==WATER)||
                    (collisions[7]->object&&collisions[7]->object->type==WATER))
            {
                player.thirst+=10;
                player.thirstCover.setSize(sf::Vector2f(120-player.thirst*1.2,player.thirstCover.getSize().y));
            }
        }
    }
}

void World::spawnEntities()
{
    if(spawningClock.getElapsedTime().asMilliseconds()>1000)
    {
        vector<int> choices{0,1,2,4};
        spawningClock.restart();
        if(rand()%10)
        {
            entityType choice = static_cast<entityType>(choices[rand()%choices.size()]);
            Entity *temp = new Entity(txtLoader,vh::randElement(chunks).randBlock().getPosition(),choice);
            temp->setTexture(*txtLoader->getEntityTexture(choice));
            if(choice==COW)
            {
                temp->setScale(0.6,0.6);
            }
            else if(choice==SHEEP)
            {
                temp->setScale(0.5,0.5);
            }
            else if(choice==PIG||choice==RABBIT)
            {
                temp->setScale(0.7,0.7);
            }
            temp->changeTextureRect(0);
            entities.push_back(temp);
        }
        else
        {
            Entity *temp4 = new Wolf(txtLoader,vh::randElement(chunks).randBlock().getPosition());
            temp4->setTexture(*txtLoader->getEntityTexture(WOLF));
            temp4->setScale(0.6,0.6);
            temp4->changeTextureRect(0);

            entities.push_back(temp4);
        }
    }
}

void World::mine(sf::RenderWindow& window)
{
    Item* holdItem = nullptr;
    if(player.eq.bar.size()>player.eq.selectedSlot)
        holdItem=player.eq.bar[player.eq.selectedSlot];
    Block* temp = getBlock(window.mapPixelToCoords(sf::Mouse::getPosition()-sf::Vector2i(33,50)));
    if(temp==nullptr||vh::distance(player.getPosition(),temp->getPosition())>=playerRange)
        return;

    if((temp->object&&temp->object->type==objectType::TREE&&holdItem&&holdItem->id==ITEMS::AXE)||
            (temp->object&&temp->object->type==objectType::BUSH&&holdItem&&holdItem->id==ITEMS::AXE)||
            (temp->object&&temp->object->type==objectType::BERRYBUSH&&holdItem&&holdItem->id==ITEMS::AXE)||
            (temp->object&&temp->object->type==objectType::WOODENFLOOR&&holdItem&&holdItem->id==ITEMS::AXE)||
            (temp->object&&temp->object->type==objectType::WOODENWALL&&holdItem&&holdItem->id==ITEMS::AXE)||
            (temp->object&&temp->object->type==objectType::STONE&&holdItem&&holdItem->id==ITEMS::PICKAXE)
            ||
            (temp->object&&temp->object->type==objectType::STONEFLOOR&&holdItem&&holdItem->id==ITEMS::PICKAXE)
            ||
            (temp->object&&temp->object->type==objectType::STONEWALL&&holdItem&&holdItem->id==ITEMS::PICKAXE))
    {
        int id = temp->object->dropID;
        temp->object=nullptr;
        temp->collision=false;

        if(id!=-1)
        {
            Item* n = new Item((ITEMS)id);
            n->setPosition(temp->getPosition());
            txtLoader->setItemTexture(*n,id);
            temp->items.push_back(n);
        }
        save(getChunkFromPos(temp->getPosition()),sf::Vector2i(temp->i,temp->j));
    }
}

void World::harvest(sf::RenderWindow& window)
{
    cerr<<"harvest"<<endl;
    Block* temp = getBlock(window.mapPixelToCoords(sf::Mouse::getPosition()-sf::Vector2i(33,50)));
    if(temp&&
            temp->object&&
            temp->object->type==BERRYBUSH&&
            static_cast<BerryBush*>(temp->object)->fruit&&
            vh::distance(temp->object->getPosition(),player.getPosition())<playerRange)
    {
        cerr<<"berrybush"<<endl;
        txtLoader->setTexture(*temp->object,BUSH,0);
        static_cast<BerryBush*>(temp->object)->fruit=false;

        Item * temp = new Item(ITEMS::BERRIES);
        temp->food=true;
        temp->setTexture(*txtLoader->getItemTexture(10));
        iface->popUp((int)temp->id);

        temp->setScale(10/6,10/6);

        player.eq.items.push_back(temp);
    }
}

void World::build(sf::RenderWindow& window)
{
    Block* temp = nullptr;
    if(player.eq.bar.size()>player.eq.selectedSlot&&player.eq.bar[player.eq.selectedSlot]->building)
    {
        temp = getBlock(window.mapPixelToCoords(sf::Mouse::getPosition()-sf::Vector2i(33,50)));
        if(!temp||temp->collision||vh::distance(player.getPosition(),temp->getPosition())>=playerRange)
            return;
        temp->object = new Object();
        objectType t;

        if(player.eq.bar[player.eq.selectedSlot]->id==ITEMS::WOODENWALLITEM)
        {
            t=objectType::WOODENWALL;
            temp->collision=true;
        }
        else if(player.eq.bar[player.eq.selectedSlot]->id==ITEMS::PLANKS)
        {
            t=objectType::WOODENFLOOR;
        }
        else if(player.eq.bar[player.eq.selectedSlot]->id==ITEMS::STONEWALLITEM)
        {
            t=objectType::STONEWALL;
            temp->collision=true;
        }
        else if(player.eq.bar[player.eq.selectedSlot]->id==ITEMS::STONEFLOORITEM)
        {
            t=objectType::STONEFLOOR;
        }

        txtLoader->setTexture(*temp->object,t,0);
        temp->object->setPosition(temp->getPosition());
    }
    if(temp)
    {
        save(getChunkFromPos(temp->getPosition()),sf::Vector2i(temp->i,temp->j));
        cerr<<"ZAPISZ ZMIANY"<<endl;
    }
}

void World::save(Chunk& chunk,sf::Vector2i id)
{
    string number="c "+std::to_string(chunk.ix)+" "+std::to_string(chunk.iy);
    string number2="b "+std::to_string(id.x)+" "+std::to_string(id.y);
    cerr<<"CHUNK = "<<number<<endl;
    string content;
    Object* obj = chunk.blocks[id.x][id.y]->object;

    if(chunk.blocks[id.x][id.y]->grass)
    {
        content+="g";
    }
    else
    {
        content+="x";
    }

    if(obj)
    {
        if(obj->type==objectType::WOODENWALL)
        {
            content+="o ";
        }
        else if(obj->type==objectType::STONEWALL)
        {
            content+="u ";
        }
        else if(obj->type==objectType::STONEFLOOR)
        {
            content+="i ";
        }
        else if(obj->type==objectType::TREE)
        {
            content+="t ";
        }
        else if(obj->type==objectType::BUSH)
        {
            content+="b ";
        }
        else if(obj->type==objectType::WATER)
        {
            content+="w ";
        }
        else if(obj->type==objectType::WOODENFLOOR)
        {
            content+="f ";
        }
        else if(obj->type==objectType::STONE)
        {
            content+="s ";
        }
        else
        {
            content+="x ";
        }
    }
    else
    {
        content+="x ";
    }

    saver->add(number,number2,content);
}

void World::draw(sf::RenderWindow& window)
{
    window.draw(player.getBackground());
    for(auto& c:chunks)
    {
        //cout<<"RYSOWANIE CHUNKA"<<endl;
        if(c.ix>player.ci-2&&c.ix<player.ci+2&&
                c.iy>player.cj-2&&c.iy<player.cj+2)
            c.draw(window);
        //cout<<"PO RYSOWANIU CHUNKA"<<endl;
    }
    //cout<<"PO WSZYSTKICH CHUNKACH"<<endl;
//    if(animationClock.getElapsedTime().asMilliseconds()>400)
//        animationClock.restart();
    player.draw(window);
    for(auto& e:entities)
    {
        window.draw(*e);
        e->block=getBlock(e->getPosition());
    }
    window.draw(daynight);
}
