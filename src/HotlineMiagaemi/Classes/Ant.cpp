#include "Ant.h"
#include "State.h"

Ant::Ant()
:m_STR(0), m_HP(0), m_INT(0), m_State(nullptr), m_Type(NONE)
{
}


Ant::~Ant()
{
}

Ant::Type Ant::getType()
{
	return m_Type;
}
