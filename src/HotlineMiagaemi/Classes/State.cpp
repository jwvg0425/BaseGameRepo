#include "State.h"


State::State()
{
}


State::~State()
{
}

bool State::isFeed()
{
	return m_IsFeed;
}

bool State::isBrainwash()
{
	return m_IsBrainwash;
}

bool State::isTrain()
{
	return m_IsTrain;
}

bool State::isInfiltrate()
{
	return m_IsInfiltrate;
}

bool State::isStatVisible()
{
	return m_IsStatVisible;
}
