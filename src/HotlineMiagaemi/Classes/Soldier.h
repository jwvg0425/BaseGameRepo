#pragma once
#include "Imago.h"
class Soldier :
    public Imago
{
public:
    Soldier(int x, int y);
    Soldier();
    virtual ~Soldier();

    Sprite*     getSprite();

	virtual bool        isEvolve();
	virtual Ant*        evolve();
	virtual void        update(float dTime);

};

