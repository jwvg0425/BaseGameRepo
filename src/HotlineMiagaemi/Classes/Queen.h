#pragma once
#include "Imago.h"
class Queen :
    public Imago
{
public:
    Queen();
    virtual ~Queen();

    Sprite*				getSprite();
    virtual bool        isEvolve();
    virtual Ant*        evolve();
    virtual void        update(float dTime);
};

