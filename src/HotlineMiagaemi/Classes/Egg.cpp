#include "Egg.h"
#include "Larva.h"

Egg::Egg()
:m_EvolveTime(10), m_Time(0)
{
    m_IsFeed = false;
    m_IsBrainwash = false;
    m_IsTrain = false;
    m_IsInfiltrate = false;
    m_IsStatVisible = false;

	m_Type = EGG;
}


Egg::~Egg()
{
}

Sprite* Egg::getSprite()
{
    return Sprite::create("egg.png");
}

bool Egg::isEvolve()
{
	if (m_EvolveTime < m_Time)
	{
		return true;
	}

	return false;
}

Ant* Egg::evolve()
{
	//TODO: 스탯 넣어주기 필요.
	Larva* larva = new Larva;

	return larva;
}

void Egg::update(float dTime)
{
	addTime(dTime);
}

void Egg::addTime(float time)
{
	m_Time += time;
}
