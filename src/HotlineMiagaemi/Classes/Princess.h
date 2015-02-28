#pragma once
#include "Imago.h"
class Princess :
    public Imago
{
public:
    Princess(int x, int y);
    Princess();
    virtual ~Princess();

    Sprite*     getSprite();

	virtual bool        isEvolve();
	virtual Ant*        evolve();
	virtual void        update(float dTime);

};

