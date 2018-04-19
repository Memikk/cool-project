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
            float choice2=objectNoise.noise0_1((float)xp*0.002,(float)yp*0.002);
            float choice3=objectNoise2.noise0_1((float)xp*0.002,(float)yp*0.002);

            blocks[i][j] = new Dirt();
            txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,DIRT,0.0);

            if(choice3>0.64)
            {
                blocks[i][j]->cover = new Sand();
                txtLoader->chooseTexture(*blocks[i][j]->cover,i,j,offsetX,offsetY,SAND,0.64,objectNoise2);
            }
            if(choice>0.30)
            {
                blocks[i][j]->grass = new Grass();
                txtLoader->chooseTexture(*blocks[i][j]->grass,i,j,offsetX,offsetY,GRASS,0.30,worldGenNoise);
            }

            if(choice>0.75)
            {
                blocks[i][j]->object = new Water();
                blocks[i][j]->collision = true;
                txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,WATER,0.75,worldGenNoise);
            }



            if(blocks[i][j]->object==nullptr)
            {
                if(choice2>0.64)
                {
                    blocks[i][j]->object = new Stone();
                    blocks[i][j]->collision=true;
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,STONE,0.64,objectNoise);
                }
                else if((choice2<0.35||(choice2>=0.35&&(int)(choice2*234)%25==0))&&choice3<=0.64)
                {
                    if((int)(choice2*100)%3)
                    {
                        blocks[i][j]->object = new Tree();
                        blocks[i][j]->collision=true;
                        txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,TREE,0,objectNoise);
                    }
                    else if((int)(choice2*10)%2)
                    {
                        blocks[i][j]->object = new Bush();
                        blocks[i][j]->collision=true;
                        txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,BUSH,0,objectNoise);
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
                    blocks[i][j]->items.push_back(new Item(0));
                    txtLoader->setItemTexture(*blocks[i][j]->items.back(),0);
                }
                else if(c==1)
                {
                    blocks[i][j]->items.push_back(new Item(1));
                    txtLoader->setItemTexture(*blocks[i][j]->items.back(),1);
                }
            }

            blocks[i][j]->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->object!=nullptr)
                blocks[i][j]->object->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->grass!=nullptr)
                blocks[i][j]->grass->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->cover!=nullptr)
                blocks[i][j]->cover->setPosition(sf::Vector2f(xp,yp));
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
            if(blocks[i][j]->object&&blocks[i][j]->object->type==WATER)
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

World::World(TextureLoader* tloader,Interface* intface)
{
    txtLoader=tloader;
    iface=intface;
    player.setPosition(0,0);
    daynight.setFillColor(sf::Color(0,0,0,0));
    daynight.setSize(sf::Vector2f(1920,1080));
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

    std::thread popChunksThread(&World::popChunks,*this,offsetX,offsetY);

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
    popChunksThread.join();
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
        item = new Item(3);
        txtLoader->setItemTexture(*item,3);
        b->object=nullptr;
        iface->popUp(3);
        player.eq.add(item);
        return;
    }
    else if(b->object&&b->object->type==CARROT)
    {
        item = new Item(4);
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
        iface->popUp(b->items.back()->id);
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
            iface->popUp(temp->id,true);
            player.eq.items.erase(player.eq.items.begin()+i);
            temp->setScale(10/6,10/6);
            temp->setPosition(b->getPosition());
            b->items.push_back(temp);
        }
    }
}

void World::takeItem(sf::Vector2f mpos)
{
    for(int i=0; i<player.eq.items.size(); i++)
    {
        if(player.eq.items[i]->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            player.eq.itemHolder = player.eq.items[i];
            player.eq.items.erase(player.eq.items.begin()+i);
            return;
        }
    }
}

void World::dropItemInEq(sf::Vector2f mpos)
{
    for(int i=0; i<player.eq.slots.size(); i++)
    {
        if(player.eq.slots[i].getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
        {
            player.eq.items.insert(player.eq.items.begin()+i,player.eq.itemHolder);
            player.eq.itemHolder=nullptr;
            return;
        }
    }
    delete player.eq.itemHolder;
    player.eq.itemHolder=nullptr;
}

void World::eat(sf::Vector2f mpos)
{
    if(player.hunger<=90)
    {
        for(int i=0; i<player.eq.items.size(); i++)
        {
            if(player.eq.items[i]->getGlobalBounds().contains(sf::Vector2f(mpos.x,mpos.y)))
            {
                if(player.eq.items[i]->food)
                {
                    player.hunger+=10;
                    player.hungerCover.setSize(sf::Vector2f(120-player.hunger*1.2,player.hungerCover.getSize().y));
                    Item *temp = player.eq.items[i];
                    iface->popUp(temp->id,true);
                    player.eq.items.erase(player.eq.items.begin()+i);
                    delete temp;
                    break;
                }
            }
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
    if(spawningClock.getElapsedTime().asMilliseconds()>3000)
    {
        spawningClock.restart();
        Entity *temp = new Sheep(txtLoader,vh::randElement(chunks).randBlock().getPosition());
        temp->setTexture(*txtLoader->getEntityTexture(SHEEP));
        temp->setScale(0.5,0.5);
        temp->changeTextureRect(0);
        entities.push_back(temp);
        Entity *temp2 = new Cow(txtLoader,vh::randElement(chunks).randBlock().getPosition());
        temp2->setTexture(*txtLoader->getEntityTexture(COW));
        temp2->setScale(0.75,0.75);
        temp2->changeTextureRect(0);
        entities.push_back(temp2);
        Entity *temp3 = new Pig(txtLoader,vh::randElement(chunks).randBlock().getPosition());
        temp3->setTexture(*txtLoader->getEntityTexture(PIG));
        temp3->setScale(0.75,0.75);
        temp3->changeTextureRect(0);
        entities.push_back(temp3);
        if(rand()%1==0)
        {
            Entity *temp4 = new Wolf(txtLoader,vh::randElement(chunks).randBlock().getPosition());
            temp4->setTexture(*txtLoader->getEntityTexture(WOLF));
            temp4->setScale(0.6,0.6);
            temp4->changeTextureRect(0);

            entities.push_back(temp4);
        }
    }
}

void World::mine()
{
    vector<Block*> collisions = getCollisions(player.getPosition());
    if(player.dir==UP&&collisions[1]->object&&collisions[1]->object->destructable)
    {
        int id = collisions[1]->object->dropID;
        collisions[1]->object=nullptr;
        collisions[1]->collision=false;

        if(id!=-1)
        {
            Item* n = new Item(id);
            n->setPosition(collisions[1]->getPosition());
            txtLoader->setItemTexture(*n,id);
            collisions[1]->items.push_back(n);
        }
    }
    else if(player.dir==RIGHT&&collisions[3]->object&&collisions[3]->object->destructable)
    {
        int id = collisions[3]->object->dropID;
        collisions[3]->object=nullptr;
        collisions[3]->collision=false;

        if(id!=-1)
        {
            Item* n = new Item(id);
            n->setPosition(collisions[3]->getPosition());
            txtLoader->setItemTexture(*n,id);
            collisions[3]->items.push_back(n);
        }
    }
    else if(player.dir==DOWN&&collisions[5]->object&&collisions[5]->object->destructable)
    {
        int id = collisions[5]->object->dropID;
        collisions[5]->object=nullptr;
        collisions[5]->collision=false;

        if(id!=-1)
        {
            Item* n = new Item(id);
            n->setPosition(collisions[5]->getPosition());
            txtLoader->setItemTexture(*n,id);
            collisions[5]->items.push_back(n);
        }
    }
    else if(player.dir==LEFT&&collisions[7]->object&&collisions[7]->object->destructable)
    {
        int id = collisions[7]->object->dropID;
        collisions[7]->object=nullptr;
        collisions[7]->collision=false;

        if(id!=-1)
        {
            Item* n = new Item(id);
            n->setPosition(collisions[7]->getPosition());
            txtLoader->setItemTexture(*n,id);
            collisions[7]->items.push_back(n);
        }
    }
}

void World::draw(sf::RenderWindow& window)
{
    window.draw(player.getBackground());
    for(auto& c:chunks)
    {
        //cout<<"RYSOWANIE CHUNKA"<<endl;
        c.draw(window);
        //cout<<"PO RYSOWANIU CHUNKA"<<endl;
    }
    //cout<<"PO WSZYSTKICH CHUNKACH"<<endl;
    if(animationClock.getElapsedTime().asMilliseconds()>500)
        animationClock.restart();
    player.draw(window);
    for(auto& e:entities)
    {
        window.draw(*e);
        e->block=getBlock(e->getPosition());
    }
    window.draw(daynight);
}
