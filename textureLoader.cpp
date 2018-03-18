#include "world.h"

void TextureLoader::chooseTexture(Block& block,vector<Block*> n)
{
    blockType type=block.type;
    if(n[0]->type!=type&&n[1]->type!=type&&n[7]->type!=type&&n[6]->type!=type&&n[5]->type!=type)
    {
        setTexture(block,type,10);
    }
    else if(n[7]->type!=type&&n[6]->type!=type&&n[5]->type!=type&&n[4]->type!=type&&n[3]->type!=type)
    {
        setTexture(block,type,11);
    }
    else if(n[5]->type!=type&&n[4]->type!=type&&n[3]->type!=type&&n[2]->type!=type&&n[1]->type!=type)
    {
        setTexture(block,type,12);
    }
    else if(n[3]->type!=type&&n[2]->type!=type&&n[1]->type!=type&&n[0]->type!=type&&n[7]->type!=type)
    {
        setTexture(block,type,9);
    }
    else if(n[7]->type!=type&&n[3]->type!=type)
    {
        setTexture(block,type,14);
    }
    else if(n[1]->type!=type&&n[5]->type!=type)
    {
        setTexture(block,type,15);
    }
    else if(n[0]->type!=type&&n[1]->type!=type&&n[7]->type!=type)
    {
        setTexture(block,type,5);
    }
    else if(n[2]->type!=type&&n[1]->type!=type&&n[3]->type!=type)
    {
        setTexture(block,type,8);
    }
    else if(n[3]->type!=type&&n[4]->type!=type&&n[5]->type!=type)
    {
        setTexture(block,type,7);
    }
    else if(n[5]->type!=type&&n[6]->type!=type&&n[7]->type!=type)
    {
        setTexture(block,type,6);
    }
    else if(n[1]->type!=type)
    {
        setTexture(block,type,4);
    }
    else if(n[3]->type!=type)
    {
        setTexture(block,type,3);
    }
    else if(n[5]->type!=type)
    {
        setTexture(block,type,2);
    }
    else if(n[7]->type!=type)
    {
        setTexture(block,type,1);
    }
    else
    {
        setTexture(block,type,0);
    }
}
void TextureLoader::chooseTexture(Block& block,int i,int j,int offsetX,int offsetY,blockType type,float value)
{
    block.i=i;
    block.j=j;
    block.offsetX=offsetX;
    block.offsetY=offsetY;

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

    if(t0<=value&&t1<=value&&t7<=value&&t6<=value&&t5<=value)
    {
        setTexture(block,type,10);
    }
    else if(t7<=value&&t6<=value&&t5<=value&&t4<=value&&t3<=value)
    {
        setTexture(block,type,11);
    }
    else if(t5<=value&&t4<=value&&t3<=value&&t2<=value&&t1<=value)
    {
        setTexture(block,type,12);
    }
    else if(t3<=value&&t2<=value&&t1<=value&&t0<=value&&t7<=value)
    {
        setTexture(block,type,9);
    }
    else if(t7<=value&&t3<=value)
    {
        setTexture(block,type,14);
    }
    else if(t1<=value&&t5<=value)
    {
        setTexture(block,type,15);
    }
    else if(t0<=value&&t1<=value&&t7<=value)
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

void TextureLoader::chooseTexture(Object& object,int i,int j,int offsetX,int offsetY,objectType type,float value)
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

    if(t0<=value&&t1<=value&&t7<=value&&t6<=value&&t5<=value)
    {
        setTexture(object,type,10);
    }
    else if(t7<=value&&t6<=value&&t5<=value&&t4<=value&&t3<=value)
    {
        setTexture(object,type,11);
    }
    else if(t5<=value&&t4<=value&&t3<=value&&t2<=value&&t1<=value)
    {
        setTexture(object,type,12);
    }
    else if(t3<=value&&t2<=value&&t1<=value&&t0<=value&&t7<=value)
    {
        setTexture(object,type,9);
    }
    else if(t7<=value&&t3<=value)
    {
        setTexture(object,type,14);
    }
    else if(t1<=value&&t5<=value)
    {
        setTexture(object,type,15);
    }
    else if(t0<=value&&t1<=value&&t7<=value)
    {
        setTexture(object,type,5);
    }
    else if(t2<=value&&t1<=value&&t3<=value)
    {
        setTexture(object,type,8);
    }
    else if(t3<=value&&t4<=value&&t5<=value)
    {
        setTexture(object,type,7);
    }
    else if(t5<=value&&t6<=value&&t7<=value)
    {
        setTexture(object,type,6);
    }
    else if(t1<=value)
    {
        setTexture(object,type,4);
    }
    else if(t3<=value)
    {
        setTexture(object,type,3);
    }
    else if(t5<=value)
    {
        setTexture(object,type,2);
    }
    else if(t7<=value)
    {
        setTexture(object,type,1);
    }
    else
    {
        setTexture(object,type,0);
    }
}

void TextureLoader::setTexture(Block& block,blockType type,int choice)
{
    //cout<<"USTAWIENIE"<<endl;
    sf::IntRect textureRect(0,choice*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    block.column=choice;
    block.type=type;
    block.setTextureRect(textureRect);
    switch(type)
    {
    case SAND:
        block.setTexture(sand);
        break;
    case GRASS:
        block.setTexture(grass);
        break;
    case DIRT:
        block.setTexture(dirt);
        break;
    }
}

void TextureLoader::setTexture(Object& object,objectType type,int choice)
{
    sf::IntRect textureRect(0,choice*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    object.type=type;
    object.column=choice;
    object.setTextureRect(textureRect);
    switch(type)
    {
    case TREE:
        object.setTexture(*tree);
        break;
    case STONE:
        object.setTexture(*stone);
        break;;
    case WATER:
        object.setTexture(*water);
        break;
    }
}

void TextureLoader::setTexture(Entity& entity,entityType type)
{
    sf::IntRect textureRect(0,BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    entity.type=type;
    entity.setTextureRect(textureRect);
    switch(type)
    {
    case SHEEP:
        entity.setTexture(*sheep,true);
        entity.setScale(0.75,0.75);
        break;
    case COW:
        entity.setTexture(*cow);
        break;
    case PIG:
        entity.setTexture(*pig);
        break;
    }
}















