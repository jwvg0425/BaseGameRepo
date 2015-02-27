#pragma once
#include "Imago.h"
class Soldier :
    public Imago
{
public:
    Soldier();
    virtual ~Soldier();

    Sprite* getSprite();

};

