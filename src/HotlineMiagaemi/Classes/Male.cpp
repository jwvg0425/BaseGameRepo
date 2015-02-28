#include "Male.h"

Male::Male(int x, int y)
{
    m_HP = 1500;
    m_STR = 200;
    m_INT = 100;
    m_Life = 500;
    m_ImagoType = IT_MALE;
    m_X = x; m_Y = y;
}

Male::Male()
{
    m_HP = 1500;
    m_STR = 200;
    m_INT = 100;
    m_Life = 500;
    m_ImagoType = IT_MALE;
}


Male::~Male()
{
}

Sprite* Male::getSprite()
{
    return Sprite::create("male_1.png");
}

bool Male::isEvolve()
{
	return false;
}

Ant* Male::evolve()
{
	return nullptr;
}

void Male::update(float dTime)
{

}
