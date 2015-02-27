#include "Princess.h"


Princess::Princess()
{
    m_HP = 300;
    m_STR = 40;
    m_INT = 40;
}


Princess::~Princess()
{
}

Sprite* Princess::getSprite()
{
    return Sprite::create("princess.png");
}
