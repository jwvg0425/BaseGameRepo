#include "Ant.h"


Ant::Ant()
:m_STR(0), m_HP(0), m_INT(0), m_State(nullptr), m_Type(NONE)
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

Ant::Type Ant::getType()
{
	return m_Type;
}
