#include "world.h"

Chunk::Chunk(int offX,int offY,siv::PerlinNoise& perlin):ix(offX),iy(offY),offsetX(offX*CHUNK_SIZE*BLOCK_SIZE),offsetY(offY*CHUNK_SIZE*BLOCK_SIZE)
{
    blocks = new Block** [CHUNK_SIZE];
    for(int i=0;i<CHUNK_SIZE;i++)
    {
        blocks[i] = new Block* [CHUNK_SIZE];
        for(int j=0;j<CHUNK_SIZE;j++)
        {
            int xp=offsetX+i*BLOCK_SIZE;
            int yp=offsetY+j*BLOCK_SIZE;
            float choice=perlin.noise0_1((float)xp*0.002,(float)yp*0.002);
            cout<<"CHOICE="<<choice<<endl;

            if(choice>0.67)
            {
                blocks[i][j] = new Water();
            }
            else if(choice>0.60)
            {
                blocks[i][j] = new Sand();
            }
            else if(choice>0.32)
            {
                blocks[i][j] = new Block();
            }
            else
            {
                blocks[i][j] = new Stone();
            }

            blocks[i][j]->setPosition(sf::Vector2f(xp,yp));
        }
    }
}

bool Chunk::operator==(const Chunk& chunk)
{
    if(ix==chunk.ix&&iy==chunk.iy) return true;
    else return false;
}

void Chunk::draw(sf::RenderWindow& window)
{
    for(int i=0;i<CHUNK_SIZE;i++)
    {
        for(int j=0;j<CHUNK_SIZE;j++)
        {
            if(!blocks[i][j]->base) window.draw(*blocks[i][j]);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~WORLD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

World::World()
{
    player.setPosition(0,0);
    perlin.reseed(8342292343489);
}

void World::generateChunks()
{
    int offsetX;
    int offsetY;
    if(player.getPosition().x>=0) offsetX=player.getPosition().x/(CHUNK_SIZE*BLOCK_SIZE);
    else offsetX=floor(player.getPosition().x/(CHUNK_SIZE*BLOCK_SIZE));

    if(player.getPosition().y>=0) offsetY=player.getPosition().y/(CHUNK_SIZE*BLOCK_SIZE);
    else offsetY=floor(player.getPosition().y/(CHUNK_SIZE*BLOCK_SIZE));

    cout<<offsetX<<" "<<offsetY<<endl;
    cout<<player.getPosition().x<<" "<<player.getPosition().y<<endl<<endl;
    if(!exist(offsetX,offsetY))
    {
        chunks.push_back(Chunk(offsetX,offsetY,perlin));
    }
}

void World::update()
{
    player.update();
}

bool World::exist(int x,int y)
{
    for(auto c:chunks)
    {
        if(c.ix==x&&c.iy==y) return true;
    }
    return false;
}

void World::draw(sf::RenderWindow& window)
{
    window.draw(player.getBackground());
    for(auto c:chunks)
    {
        c.draw(window);
    }
    player.draw(window);
}
