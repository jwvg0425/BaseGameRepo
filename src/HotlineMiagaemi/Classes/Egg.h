#pragma once
#include "State.h"

class Egg :
    public State
{
public:
    Egg();
    virtual ~Egg();

    Sprite* getSprite();
private:
    int m_EvolveTime;
};

