#include "Imago.h"
#include "TunnelManager.h"

Imago::Imago()
{
    m_IsFeed = true;
    m_IsBrainwash = true;
    m_IsTrain = true;
    m_IsInfiltrate = true;
    m_IsStatVisible = true;
	m_Satiety = 70;
	m_Dir = DIR_DOWN;

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

    ant->isAttacked(m_STR);
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
        if (m_Y <= MAX_DEEP)
            break;
		m_Dir = DIR_DOWN;
        m_Y--;
        break;
    case 1:
        if (m_Y >= 0)
            break;
		m_Dir = DIR_UP;
        m_Y++;
        break;
    case 2:
        if (m_X <= -1)
            break;
        m_X--;
		m_Dir = DIR_LEFT;
        break;
    case 3:
        if (m_X >= 1)
            break;
        m_X++;
		m_Dir = DIR_RIGHT;
        break;
    }
}
