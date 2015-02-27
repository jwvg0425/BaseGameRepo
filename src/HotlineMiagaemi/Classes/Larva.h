#pragma once
#include "State.h"
class Larva :
    public State
{
public:
    Larva();
    virtual ~Larva();

    Sprite* getSprite();

	virtual bool isEvolve();

	virtual State* evolve();

	virtual void update(float dTime);

protected:
    int m_Satiety;
};

