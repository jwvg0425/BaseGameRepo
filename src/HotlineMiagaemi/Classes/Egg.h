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

	static int getEvolveTime();

private:
    static const int EVOLVE_TIME;
	float m_Time;
};

