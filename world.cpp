#include "world.h"

Chunk::Chunk(int offX,int offY,siv::PerlinNoise& perlin,TextureLoader* txtLoader):ix(offX),iy(offY),offsetX(offX*CHUNK_SIZE*BLOCK_SIZE),offsetY(offY*CHUNK_SIZE*BLOCK_SIZE)
{
    blocks = new Block** [CHUNK_SIZE];
    for(int i=0; i<CHUNK_SIZE; i++)
    {
        blocks[i] = new Block* [CHUNK_SIZE];
        for(int j=0; j<CHUNK_SIZE; j++)
        {
            int xp=offsetX+i*BLOCK_SIZE;
            int yp=offsetY+j*BLOCK_SIZE;

            float perlin2choice=objectNoise.noise0_1((float)xp*0.002,(float)yp*0.002);

            float choice=worldGenNoise.noise0_1((float)xp*0.002,(float)yp*0.002);

            if(choice>0.74)
            {
                blocks[i][j] = new Water();
                txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,WATER,0.74);
                water.push_back(blocks[i][j]);
            }
            else if(choice>0.64)
            {
                blocks[i][j] = new Sand();

                txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,SAND,0.64);

                sand.push_back(blocks[i][j]);
            }
            else if(choice>0.32)
            {
                if(perlin2choice<0.60)
                {
                    if((static_cast<int>(perlin2choice*100)%5))
                        blocks[i][j] = new Grass();
                    else
                    {
                        blocks[i][j] = new Grass(false,true);
                        txtLoader->setPlantTexture(*blocks[i][j]);
                    }
                }
                else
                {
                    blocks[i][j] = new Grass(true);
                    txtLoader->setTreeTexture(*blocks[i][j]);
                }
                grass.push_back(static_cast<Grass*>(blocks[i][j]));
            }
            else
            {
                blocks[i][j] = new Stone();
                txtLoader->chooseTexture(*blocks[i][j],i,j,offsetX,offsetY,STONE,0.32);
                stone.push_back(blocks[i][j]);
            }

            blocks[i][j]->setPosition(sf::Vector2f(xp,yp));
            blocks[i][j]->initialize();
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
    for(auto &w:water)
    {
        w->animate();
        w->draw(window);
    }
    for(auto &s:sand) s->draw(window);
    for(auto &s:stone) s->draw(window);
    for(auto &g:grass) window.draw(g->object);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~WORLD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

World::World(TextureLoader* tloader)
{
    txtLoader=tloader;
    player.setPosition(0,0);
    perlin.reseed(843469);
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
    popChunks(offsetX,offsetY);
}

void World::popChunks(int x,int y)
{
    for(int i=chunks.size()-1;i>=0;i--)
    {
        if(x+2<chunks[i].ix||x-2>chunks[i].ix) chunks.erase(chunks.begin()+i);
        if(y+2<chunks[i].iy||y-2>chunks[i].iy) chunks.erase(chunks.begin()+i);
    }
}

void World::update()
{
    vector<bool> collisions;
    if(!player.animating)
    {
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x-BLOCK_SIZE,player.getPosition().y-BLOCK_SIZE)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x,player.getPosition().y-BLOCK_SIZE)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x+BLOCK_SIZE,player.getPosition().y-BLOCK_SIZE)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x+BLOCK_SIZE,player.getPosition().y)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x+BLOCK_SIZE,player.getPosition().y+BLOCK_SIZE)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x,player.getPosition().y+BLOCK_SIZE)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x-BLOCK_SIZE,player.getPosition().y+BLOCK_SIZE)));
        collisions.push_back(blockCollision(sf::Vector2f(player.getPosition().x-BLOCK_SIZE,player.getPosition().y)));
    }

    player.update(collisions);
}

bool World::exist(int x,int y)
{
    for(auto c:chunks)
    {
        if(c.ix==x&&c.iy==y)
            return true;
    }
    return false;
}

bool World::blockCollision(sf::Vector2f pos)
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

    if(getChunk(ox,oy).blocks[ix][iy]->collision)
        return true;
    else
        return false;
}

Chunk& World::getChunk(int x,int y)
{
    for(auto &c:chunks)
    {
        if(c.ix==x&&c.iy==y)
            return c;
    }
}

void World::draw(sf::RenderWindow& window)
{
    window.draw(player.getBackground());
    for(auto c:chunks)
    {
        c.draw(window);
    }
    if(animationClock.getElapsedTime().asMilliseconds()>500)
        animationClock.restart();
    player.draw(window);
}
