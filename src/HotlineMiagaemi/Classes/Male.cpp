#include "Male.h"


Male::Male()
{
    m_HP = 500;
    m_STR = 100;
    m_INT = 50;
}


Male::~Male()
{
}

Sprite* Male::getSprite()
{
    return Sprite::create("male.png");
}
