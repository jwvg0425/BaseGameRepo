#include "Soldier.h"


Soldier::Soldier()
{
    m_HP = 400;
    m_STR = 150;
    m_INT = 0;
}


Soldier::~Soldier()
{
}

Sprite* Soldier::getSprite()
{
    return Sprite::create("soldier.png");
}
