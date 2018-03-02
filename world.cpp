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
            int xp1,xp2,xp3,xp4,xp5,xp6,xp7,xp8;
            int yp1,yp2,yp3,yp4,yp5,yp6,yp7,yp8;

            xp1=offsetX+(i-1)*BLOCK_SIZE;
            xp2=offsetX+i    *BLOCK_SIZE;
            xp3=offsetX+(i+1)*BLOCK_SIZE;
            xp4=offsetX+(i+1)*BLOCK_SIZE;
            xp5=offsetX+(i+1)*BLOCK_SIZE;
            xp6=offsetX+i    *BLOCK_SIZE;
            xp7=offsetX+(i-1)*BLOCK_SIZE;
            xp8=offsetX+(i-1)*BLOCK_SIZE;

            yp1=offsetY+(j-1)*BLOCK_SIZE;
            yp2=offsetY+(j-1)*BLOCK_SIZE;
            yp3=offsetY+(j-1)*BLOCK_SIZE;
            yp4=offsetY+j    *BLOCK_SIZE;
            yp5=offsetY+(j+1)*BLOCK_SIZE;
            yp6=offsetY+(j+1)*BLOCK_SIZE;
            yp7=offsetY+(j+1)*BLOCK_SIZE;
            yp8=offsetY+j    *BLOCK_SIZE;

            float choice=perlin.noise0_1((float)xp*0.002,(float)yp*0.002);

            if(choice>0.74)
            {
                blocks[i][j] = new Water();
                txtLoader->setWaterTexture(*blocks[i][j]);
            }
            else if(choice>0.60)
            {
                blocks[i][j] = new Sand();
                float t0=perlin.noise0_1((float)xp1*0.002,(float)yp1*0.002);
                float t1=perlin.noise0_1((float)xp2*0.002,(float)yp2*0.002);
                float t2=perlin.noise0_1((float)xp3*0.002,(float)yp3*0.002);
                float t3=perlin.noise0_1((float)xp4*0.002,(float)yp4*0.002);
                float t4=perlin.noise0_1((float)xp5*0.002,(float)yp5*0.002);
                float t5=perlin.noise0_1((float)xp6*0.002,(float)yp6*0.002);
                float t6=perlin.noise0_1((float)xp7*0.002,(float)yp7*0.002);
                float t7=perlin.noise0_1((float)xp8*0.002,(float)yp8*0.002);

                if(t0<=0.60&&t1<=0.60&&t7<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],5);
                }
                else if(t2<=0.60&&t1<=0.60&&t3<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],6);
                }
                else if(t3<=0.60&&t4<=0.60&&t5<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],8);
                }
                else if(t5<=0.60&&t6<=0.60&&t7<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],7);
                }
                else if(t1<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],4);
                }
                else if(t3<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],3);
                }
                else if(t5<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],2);
                }
                else if(t7<=0.60)
                {
                    txtLoader->setSandTexture(*blocks[i][j],1);
                }
                else
                {
                    txtLoader->setSandTexture(*blocks[i][j],0);
                }
            }
            else if(choice>0.32)
            {
                blocks[i][j] = new Grass();
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
            if(!blocks[i][j]->base)
                window.draw(*blocks[i][j]);
            blocks[i][j]->animate();
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~WORLD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
}

void World::update()
{
    player.update();
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

void World::draw(sf::RenderWindow& window)
{
    window.draw(player.getBackground());
    for(auto c:chunks)
    {
        c.draw(window);
    }
    player.draw(window);
}
