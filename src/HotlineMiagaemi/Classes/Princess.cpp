#include "Princess.h"

Princess::Princess(int x, int y)
{
    m_HP = 300;
    m_STR = 40;
    m_INT = 40;
    m_Life = 300;
    m_ImagoType = IT_PRINCESS;
    m_X = x; m_Y = y;
}

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

bool Princess::isEvolve()
{
	return false;
}

Ant* Princess::evolve()
{
	return nullptr;
}

void Princess::update(float dTime)
{

}
