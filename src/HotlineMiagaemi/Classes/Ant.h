#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Ant
{
public:
	enum StateType
	{
		ST_NONE = 0,
		ST_EGG = 1,
		ST_LARVA = 2,
		ST_IMAGO = 3,
	};

    Ant();
    virtual ~Ant();

    virtual Sprite* getSprite() = 0;

	virtual bool isEvolve() = 0;

	virtual Ant* evolve() = 0;

	virtual void update(float dTime) = 0;

	StateType getType();

    void setHP(int Damage);

	bool isFeed();
	bool isBrainwash();
	bool isTrain();
	bool isInfiltrate();
	bool isStatVisible();

protected:
	int     m_STR;
	int     m_HP;
	int     m_INT;
    int     m_Life;
	Sprite* m_Sprite;
	Ant*    m_State;
	StateType	m_Type;

    bool        m_IsFeed;
    bool        m_IsBrainwash;
    bool        m_IsTrain;
    bool        m_IsInfiltrate;
    bool        m_IsStatVisible;
};

