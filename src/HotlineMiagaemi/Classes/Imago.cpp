#include "Imago.h"


Imago::Imago()
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = true;
    m_IsInfiltrate = true;
    m_IsStatVisible = true;
}


Imago::~Imago()
{
}

Sprite* Imago::getSprite()
{
    return Sprite::create("imago.png");
}
