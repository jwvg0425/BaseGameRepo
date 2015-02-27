#pragma once
#include "Ant.h"
class Larva :
    public Ant
{
public:
    Larva();
    virtual ~Larva();

    Sprite* getSprite();

	virtual bool isEvolve();

	virtual Ant* evolve();

	virtual void update(float dTime);
private:
	static const int SATIETY_EVOLVE_VALUE;
};

