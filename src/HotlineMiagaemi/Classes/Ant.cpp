#include "Ant.h"


Ant::Ant()
:m_STR(0), m_HP(0), m_INT(0), m_Life(0), m_Age(0), m_Type(ST_NONE), m_Satiety(0)
{
}


Ant::~Ant()
{
}

bool Ant::isFeed()
{
	return m_IsFeed;
}

bool Ant::isBrainwash()
{
	return m_IsBrainwash;
}

bool Ant::isTrain()
{
	return m_IsTrain;
}

bool Ant::isInfiltrate()
{
	return m_IsInfiltrate;
}

bool Ant::isStatVisible()
{
	return m_IsStatVisible;
}

Ant::StateType Ant::getType()
{
	return m_Type;
}

void Ant::setHP(int Damage)
{
    m_HP -= Damage;
}

void Ant::addSatiety(int satiety)
{
	m_Satiety += satiety;
}

void Ant::addAge(int age)
{
	m_Age += age;
}

void Ant::addInt(int val)
{
	m_INT += val;
}

int Ant::getHp()
{
	return m_HP;
}

int Ant::getStr()
{
	return m_STR;
}

int Ant::getInt()
{
	return m_INT;
}

int Ant::getLife()
{
	return m_Life;
}

int Ant::getSatiety()
{
	return m_Satiety;
}

int Ant::getAge()
{
	return m_Age;
}

bool Ant::isDead()
{
	//수명 다 되거나, 배가 너무 고프거나, 체력이 없으면 사망함
	if (m_Satiety < 0)
	{
		return true;
	}

	if (m_Type == ST_IMAGO)
	{
		if (m_Age > m_Life || m_HP < 0)
		{
			return true;
		}
	}

	return false;
}

void Ant::addStr(int str)
{
	m_STR += str;
}

void Ant::addHp(int hp)
{
	m_HP += hp;
}
