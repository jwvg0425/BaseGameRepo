#pragma once
#include "Ant.h"
class State :
    public Ant
{
public:
    State();
    virtual ~State();

protected:
    bool m_IsFeed;
    bool m_IsBrainwash;
    bool m_IsTrain;
    bool m_IsInfiltrate;
    bool m_IsStatVisible;
};

