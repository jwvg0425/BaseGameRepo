#pragma once
#include "cocos2d.h"
class State;

USING_NS_CC;

class Ant
{
public:
	enum Type
	{
		NONE = 0,
		EGG = 1,
		LARVA = 2,
		IMAGO = 3,
	};

    Ant();
    virtual ~Ant();

    virtual Sprite* getSprite() = 0;

	virtual bool isEvolve() = 0;

	virtual State* evolve() = 0;
	
	virtual void update(float dTime) = 0;

	Type getType();
	
protected:
	
    int     m_STR;
    int     m_HP;
    int     m_INT;
    Sprite* m_Sprite;
    State*  m_State;
	Type	m_Type;
};

