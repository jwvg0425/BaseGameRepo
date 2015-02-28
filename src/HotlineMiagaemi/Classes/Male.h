#pragma once
#include "Imago.h"
class Male :
    public Imago
{
public:
    Male(int x, int y);
    Male();
    virtual ~Male();

    Sprite*				getSprite();
	virtual bool        isEvolve();
	virtual Ant*        evolve();
	virtual void        update(float dTime);
};

