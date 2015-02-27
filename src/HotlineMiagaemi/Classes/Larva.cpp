#include "Larva.h"
#include "Worker.h"
#include "Male.h"
#include "Princess.h"
#include "Soldier.h"


Larva::Larva()
:m_Satiety(0)
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = false;
    m_IsInfiltrate = false;
    m_IsStatVisible = true;

	m_Type = ST_LARVA;
}


Larva::~Larva()
{
}

Sprite* Larva::getSprite()
{
    return Sprite::create("larva_1.png");
}

bool Larva::isEvolve()
{
	return false;
}

Ant* Larva::evolve()
{
	int randomValue = rand() % 100;
	Ant* evolveAnt;

	if (randomValue < 70)
	{
		evolveAnt = new Worker;
	}
	else if (randomValue < 90)
	{
		evolveAnt = new Soldier;
	}
	else if (randomValue < 96)
	{
		evolveAnt = new Princess;
	}
	else
	{
		evolveAnt = new Male;
	}

	return evolveAnt;
}

void Larva::update(float dTime)
{

}
