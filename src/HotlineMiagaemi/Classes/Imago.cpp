#include "Imago.h"


Imago::Imago()
:m_Satiety(70)
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = true;
    m_IsInfiltrate = true;
    m_IsStatVisible = true;

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

Imago::ImagoType Imago::getType()
{
	return m_ImagoType;
}
