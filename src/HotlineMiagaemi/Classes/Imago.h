#pragma once
#include "State.h"
class Imago :
    public State
{
public:
    Imago();
    virtual ~Imago();

    Sprite* getSprite();

};

