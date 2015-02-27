#pragma once
class State;
class Ant
{
public:
    Ant();
    virtual ~Ant();

private:
    int     m_STR;
    int     m_HP;
    int     m_INT;
    State*  m_State;
};

