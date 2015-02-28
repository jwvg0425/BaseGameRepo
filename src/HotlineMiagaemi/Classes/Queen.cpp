#include "Queen.h"


Queen::Queen()
{
    m_HP = 1000;
    m_STR = 50;
}

Queen::Queen(int x, int y)
{
    m_HP = 1000;
    m_STR = 50;
    m_X = x;
    m_Y = y;
}


Queen::~Queen()
{
}

Sprite* Queen::getSprite()
{
    return nullptr;
}

bool Queen::isEvolve()
{
    return false;
}

Ant* Queen::evolve()
{
    return nullptr;
}

void Queen::update(float dTime)
{

}
