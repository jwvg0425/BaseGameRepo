#pragma once
#include "Imago.h"
class Male :
    public Imago
{
public:
    Male();
    virtual ~Male();

    Sprite* getSprite();
};

