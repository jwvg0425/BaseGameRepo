#include "Princess.h"


Princess::Princess()
{
    m_HP = 300;
    m_STR = 40;
    m_INT = 40;
    m_Life = 300;
    m_ImagoType = IT_PRINCESS;
}


Princess::~Princess()
{
}

Sprite* Princess::getSprite()
{
    return Sprite::create("princess.png");
}
