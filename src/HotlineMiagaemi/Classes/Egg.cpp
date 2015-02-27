#include "Egg.h"


Egg::Egg()
:m_EvolveTime(10)
{
    m_IsFeed = false;
    m_IsBrainwash = false;
    m_IsTrain = false;
    m_IsInfiltrate = false;
    m_IsStatVisible = false;
}


Egg::~Egg()
{
}

Sprite* Egg::getSprite()
{
    return Sprite::create("egg.png");
}
