#pragma once
#include "Ant.h"
class Imago :
    public Ant
{
public:
    Imago();
    virtual ~Imago();

    virtual Sprite* getSprite() = 0;

	virtual bool isEvolve() = 0;

	virtual Ant* evolve() = 0;

	virtual void update(float dTime) = 0;

private:
    int m_Satiety;
protected:

};

