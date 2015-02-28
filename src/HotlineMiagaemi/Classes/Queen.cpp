#include "Queen.h"


Queen::Queen()
{
    m_HP = 1000;
    m_STR = 50;
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
