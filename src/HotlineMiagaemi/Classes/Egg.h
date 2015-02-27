#pragma once
#include "State.h"

class Egg :
    public State
{
public:
    Egg();
    virtual ~Egg();

    Sprite* getSprite();
	void addTime(float time);

	virtual bool isEvolve();

	virtual Ant* evolve();

	virtual void update(float dTime);

private:
    int m_EvolveTime;
	float m_Time;
};

