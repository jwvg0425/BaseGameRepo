#include "Soldier.h"

Soldier::Soldier(int x, int y)
{
    m_HP = 1500;
    m_STR = 200;
    m_INT = 100;
    m_Life = 500;
    m_ImagoType = IT_SOLDIER;
    m_X = x; m_Y = y;
}

Soldier::Soldier()
{
    m_HP = 400;
    m_STR = 150;
    m_INT = 5;
    m_Life = 300;
    m_ImagoType = IT_SOLDIER;
}


Soldier::~Soldier()
{
}

Sprite* Soldier::getSprite()
{
    return Sprite::create("soldier_1.png");
}

bool Soldier::isEvolve()
{
	return false;
}

Ant* Soldier::evolve()
{
	return nullptr;
}

void Soldier::update(float dTime)
{

}
