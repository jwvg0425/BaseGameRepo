#pragma once
#include "Ant.h"

class Egg :
    public Ant
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

