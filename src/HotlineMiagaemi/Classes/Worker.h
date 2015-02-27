#pragma once
#include "Imago.h"
class Worker :
    public Imago
{
public:
    Worker();
    virtual ~Worker();

    Sprite*     getSprite();
    ImagoType   getType(){ return m_ImagoType; }
};

