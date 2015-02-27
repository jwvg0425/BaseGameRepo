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

private:
    int     m_STR;
    int     m_HP;
    int     m_INT;
    Sprite* m_Sprite;
    State*  m_State;
};

