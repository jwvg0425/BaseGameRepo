#pragma once
#include "Imago.h"
class Princess :
    public Imago
{
public:
    Princess();
    virtual ~Princess();

    Sprite*     getSprite();
    ImagoType   getType(){ return m_ImagoType; }

};

