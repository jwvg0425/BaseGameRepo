#include "Ant.h"


Ant::Ant()
:m_STR(0), m_HP(0), m_INT(0), m_Type(ST_NONE), m_Satiety(0)
{
}


Ant::~Ant()
{
}

bool Ant::isFeed()
{
	return m_IsFeed;
}

bool Ant::isBrainwash()
{
	return m_IsBrainwash;
}

bool Ant::isTrain()
{
	return m_IsTrain;
}

bool Ant::isInfiltrate()
{
	return m_IsInfiltrate;
}

bool Ant::isStatVisible()
{
	return m_IsStatVisible;
}

Ant::StateType Ant::getType()
{
	return m_Type;
}

void Ant::setHP(int Damage)
{
    m_HP -= Damage;
}

void Ant::addSatiety(int satiety)
{
	m_Satiety += satiety;
}

void Ant::addLife(int life)
{
	m_Life += life;
}

void Ant::addInt(int val)
{
	m_INT += val;
}
