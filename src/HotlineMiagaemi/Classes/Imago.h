#pragma once
#include "State.h"
class Imago :
    public State
{
public:
    Imago();
    virtual ~Imago();

    virtual Sprite* getSprite() = 0;

	virtual bool isEvolve() = 0;

	virtual State* evolve() = 0;

	virtual void update(float dTime) = 0;

private:
    int m_Satiety;
protected:

};

