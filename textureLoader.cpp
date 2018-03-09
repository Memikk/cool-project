#include "world.h"

void TextureLoader::chooseTexture(Block& block,int i,int j,int offsetX,int offsetY,blockType type,float value)
{
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

    float t0=worldGenNoise.noise0_1((float)xp1*0.002,(float)yp1*0.002);
    float t1=worldGenNoise.noise0_1((float)xp2*0.002,(float)yp2*0.002);
    float t2=worldGenNoise.noise0_1((float)xp3*0.002,(float)yp3*0.002);
    float t3=worldGenNoise.noise0_1((float)xp4*0.002,(float)yp4*0.002);
    float t4=worldGenNoise.noise0_1((float)xp5*0.002,(float)yp5*0.002);
    float t5=worldGenNoise.noise0_1((float)xp6*0.002,(float)yp6*0.002);
    float t6=worldGenNoise.noise0_1((float)xp7*0.002,(float)yp7*0.002);
    float t7=worldGenNoise.noise0_1((float)xp8*0.002,(float)yp8*0.002);
    float t8=worldGenNoise.noise0_1((float)xp9*0.002,(float)yp7*0.002);
    float t9=worldGenNoise.noise0_1((float)xp10*0.002,(float)yp8*0.002);
    float t10=worldGenNoise.noise0_1((float)xp11*0.002,(float)yp7*0.002);
    float t11=worldGenNoise.noise0_1((float)xp12*0.002,(float)yp8*0.002);
    float t12=worldGenNoise.noise0_1((float)xp13*0.002,(float)yp8*0.002);
    float t13=worldGenNoise.noise0_1((float)xp14*0.002,(float)yp8*0.002);
    float t14=worldGenNoise.noise0_1((float)xp15*0.002,(float)yp8*0.002);

    if(t0<=value&&t1<=value&&t7<=value)
    {
        setTexture(block,type,5);
    }
    else if(t2<=value&&t1<=value&&t3<=value)
    {
        setTexture(block,type,8);
    }
    else if(t3<=value&&t4<=value&&t5<=value)
    {
        setTexture(block,type,7);
    }
    else if(t5<=value&&t6<=value&&t7<=value)
    {
        setTexture(block,type,6);
    }
    else if(t1<=value)
    {
        setTexture(block,type,4);
    }
    else if(t3<=value)
    {
        setTexture(block,type,3);
    }
    else if(t5<=value)
    {
        setTexture(block,type,2);
    }
    else if(t7<=value)
    {
        setTexture(block,type,1);
    }





    else
    {
        setTexture(block,type,0);
    }




}

void TextureLoader::setTexture(Block& block,blockType type,int choice)
{
    sf::IntRect textureRect(0,choice*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    block.type=choice;
    block.setTextureRect(textureRect);
    switch(type)
    {
    case SAND:
        block.setTexture(sand);
        break;
    case WATER:
        block.setTexture(water);
        break;
    case STONE:
        block.setTexture(stone);
        break;
    }
}















