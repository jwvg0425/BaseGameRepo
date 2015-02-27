#pragma once
#include "Imago.h"
class Worker :
    public Imago
{
public:
    Worker();
    virtual ~Worker();

    Sprite* getSprite();

};

