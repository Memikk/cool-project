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

            float objectPerlin=objectNoise.noise0_1((float)xp*0.002,(float)yp*0.002);
            float dirtPerlin=dirtNoise.noise0_1((float)xp*0.002,(float)yp*0.002);
            float choice=worldGenNoise.noise0_1((float)xp*0.002,(float)yp*0.002);

            if(dirtPerlin<0.30&&choice<=0.64)
            {
                blocks[i][j] = new Dirt();
                txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,DIRT,0.20);
            }

//            if(choice>0.74)
//            {
//                blocks[i][j] = new Water();
//                txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,WATER,0.74);
//            }
            else if(choice>0.64)
            {
                blocks[i][j] = new Sand();
                txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,SAND,0.64);
                if(choice>0.75)
                {
                    blocks[i][j]->object = new Water();
                    blocks[i][j]->collision = true;
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,WATER,0.75);
                }
            }
            else
            {
                if(blocks[i][j]==nullptr)
                {
                    blocks[i][j] = new Grass();
                    txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,GRASS,0);
                }

                if(objectPerlin<0.45&&(int)(objectPerlin*100)%3)
                {
                    blocks[i][j]->object = new Tree();
                    blocks[i][j]->collision=true;
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,TREE,0);
                }
                else if(objectPerlin>0.65)
                {
                    blocks[i][j]->object = new Stone();
                    blocks[i][j]->collision=true;
                    txtLoader->chooseTexture(*blocks[i][j]->object,i,j,offsetX,offsetY,STONE,0);
                }
            }

            blocks[i][j]->setPosition(sf::Vector2f(xp,yp));
            if(blocks[i][j]->object!=nullptr)
                blocks[i][j]->object->setPosition(sf::Vector2f(xp,yp));
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
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~WORLD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

World::World(TextureLoader* tloader)
{
    txtLoader=tloader;
    player.setPosition(0,0);
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

void World::updateEntities()
{
    for(auto& e:entities)
    {
        e->update();
    }
}

void World::update()
{
    //cout<<"TWORZENIE KOLIZJI"<<endl;
    std::thread ue(&World::updateEntities,*this);
    vector<Block*> collisions;
    sf::Vector2f ppos=player.getPosition()+sf::Vector2f(BLOCK_SIZE/2.f,BLOCK_SIZE/2.f);
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x-BLOCK_SIZE,ppos.y-BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x,ppos.y-BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x+BLOCK_SIZE,ppos.y-BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x+BLOCK_SIZE,ppos.y)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x+BLOCK_SIZE,ppos.y+BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x,ppos.y+BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x-BLOCK_SIZE,ppos.y+BLOCK_SIZE)));
    collisions.push_back(blockCollision(sf::Vector2f(ppos.x-BLOCK_SIZE,ppos.y)));

    for(auto& c:collisions)
        c->setFillColor(sf::Color::Red);

    //cout<<"PLAYER UPDATE"<<endl;
    player.update(collisions);

    ue.join();
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

    int ix,iy;
    int tx,ty;

    tx=ox*CHUNK_SIZE*BLOCK_SIZE;
    ty=oy*CHUNK_SIZE*BLOCK_SIZE;

    ix=abs((pos.x-tx)/BLOCK_SIZE);
    iy=abs((pos.y-ty)/BLOCK_SIZE);

    return getChunk(ox,oy)->blocks[ix][iy];
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

void World::spawnEntities()
{
    if(spawningClock.getElapsedTime().asSeconds()>1.0)
    {
        spawningClock.restart();
        cout<<"wrzucanie owcy"<<endl;
        Entity *temp = new Sheep(vh::randomPos(600,player));
        txtLoader->setTexture(*temp,SHEEP);
        entities.push_back(temp);
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
    }
}
