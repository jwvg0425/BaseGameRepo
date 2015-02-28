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

    void isAttacked(int Damage);

	bool isFeed();
	bool isBrainwash();
	bool isTrain();
	bool isInfiltrate();
	bool isStatVisible();

	bool isDead();

	void addSatiety(int satiety);
	void addAge(int age);
	void addInt(int val);
	void addStr(int str);
	void addHp(int hp);

	int getHp();
	int getStr();
	int getInt();
	int getLife();
	int getAge();
	int getSatiety();

protected:
	int     m_STR;
	int     m_HP;
	int     m_INT;
    int     m_Life;
	int		m_Age;
	Sprite* m_Sprite;
	int		m_Satiety;

	StateType	m_Type;

    bool        m_IsFeed;
    bool        m_IsBrainwash;
    bool        m_IsTrain;
    bool        m_IsInfiltrate;
    bool        m_IsStatVisible;
};

