#include "Soldier.h"


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
    return Sprite::create("soldier.png");
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
