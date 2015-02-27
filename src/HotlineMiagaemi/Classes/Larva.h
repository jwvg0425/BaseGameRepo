#pragma once
#include "State.h"
class Larva :
    public State
{
public:
    Larva();
    virtual ~Larva();

    Sprite* getSprite();

protected:
};

