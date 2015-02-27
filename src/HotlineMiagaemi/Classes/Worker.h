#pragma once
#include "Imago.h"
class Worker :
    public Imago
{
public:
    Worker();
    virtual ~Worker();

    Sprite*     getSprite();

	virtual bool        isEvolve();
	virtual Ant*        evolve();
	virtual void        update(float dTime);
};

