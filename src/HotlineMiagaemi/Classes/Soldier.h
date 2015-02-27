#pragma once
#include "Imago.h"
class Soldier :
    public Imago
{
public:
    Soldier();
    virtual ~Soldier();

    Sprite*     getSprite();

	virtual bool        isEvolve();
	virtual Ant*        evolve();
	virtual void        update(float dTime);

};

