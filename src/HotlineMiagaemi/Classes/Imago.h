#pragma once
#include "State.h"
class Imago :
    public State
{
public:
    Imago();
    virtual ~Imago();

    virtual Sprite* getSprite() = 0;

private:
    int m_Satiety;
protected:

};

