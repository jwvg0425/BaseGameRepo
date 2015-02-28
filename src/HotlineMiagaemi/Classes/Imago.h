#pragma once
#include "Ant.h"
class Imago :
    public Ant
{
public:
    Imago();
    virtual ~Imago();

    enum ImagoType{
        IT_WORKER,
        IT_MALE,
        IT_PRINCESS,
        IT_SOLDIER
    };

    virtual Sprite*     getSprite() = 0;
	virtual bool        isEvolve() = 0;
	virtual Ant*        evolve() = 0;
	virtual void        update(float dTime) = 0;

    ImagoType			getImagoType();

    void                disguise(int pheromoneTime, ImagoType type);

    void                attack(Ant* ant);

    void                setPos(int x, int y);
    int                 getPosX(){ return m_X; }
    int                 getPosY(){ return m_Y; }

    void                move();

protected:
    int         m_PheromoneTime;
    int         m_X;
    int         m_Y;
    ImagoType   m_ImagoType;
};

