#pragma once
#include "cocos2d.h"

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

	virtual Ant* evolve() = 0;

	virtual void update(float dTime) = 0;

	Type getType();

	bool isFeed();
	bool isBrainwash();
	bool isTrain();
	bool isInfiltrate();
	bool isStatVisible();

protected:
	int     m_STR;
	int     m_HP;
	int     m_INT;
	Sprite* m_Sprite;
	Ant*  m_State;
	Type	m_Type;

    bool        m_IsFeed;
    bool        m_IsBrainwash;
    bool        m_IsTrain;
    bool        m_IsInfiltrate;
    bool        m_IsStatVisible;
};

