#include "Imago.h"


Imago::Imago()
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = true;
    m_IsInfiltrate = true;
    m_IsStatVisible = true;
	m_Satiety = 70;

	m_Type = ST_IMAGO;
}


Imago::~Imago()
{
}

void Imago::disguise(int pheromoneTime, ImagoType type)
{
    m_PheromoneTime = pheromoneTime;
    m_ImagoType = type;
}

void Imago::attack(Ant* ant)
{
    if (ant == nullptr)
        return;

    ant->setHP(m_STR);
}

Imago::ImagoType Imago::getImagoType()
{
	return m_ImagoType;
}

void Imago::setPos(int x, int y)
{
    m_X = x;
    m_Y = y;
}

void Imago::move()
{
    int dir = rand() % 4;

    switch (dir)
    {
    case 0:
        m_Y--;
        break;
    case 1:
        m_Y++;
        break;
    case 2:
        m_X--;
        break;
    case 3:
        m_X++;
        break;
    }
}
