#pragma once
#include "Ant.h"

class State :
    public Ant
{
public:
    State();
    virtual ~State();

    virtual Sprite* getSprite() = 0;

	virtual bool isEvolve() = 0;

	virtual State* evolve() = 0;

	virtual void update(float dTime) = 0;

	bool isFeed();
	bool isBrainwash();
	bool isTrain();
	bool isInfiltrate();
	bool isStatVisible();

protected:
    bool        m_IsFeed;
    bool        m_IsBrainwash;
    bool        m_IsTrain;
    bool        m_IsInfiltrate;
    bool        m_IsStatVisible;
};

