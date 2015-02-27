#pragma once
#include "cocos2d.h"
class State;

USING_NS_CC;

class Ant
{
public:
    Ant();
    virtual ~Ant();

    virtual Sprite* getSprite() = 0;

	virtual bool isEvolve() = 0;

	virtual Ant* evolve() = 0;
	
	virtual void update(float dTime) = 0;

protected:
    int     m_STR;
    int     m_HP;
    int     m_INT;
    Sprite* m_Sprite;
    State*  m_State;
};

