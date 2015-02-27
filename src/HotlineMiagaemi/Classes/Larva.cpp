#include "Larva.h"


Larva::Larva()
:m_Satiety(0)
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = false;
    m_IsInfiltrate = false;
    m_IsStatVisible = true;
}


Larva::~Larva()
{
}

Sprite* Larva::getSprite()
{
    return Sprite::create("larva1.png");
}
