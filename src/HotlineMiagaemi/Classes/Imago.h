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

    virtual ImagoType   getType() = 0;

    void                disguise(int pheromoneTime, ImagoType type);

    void                attack(Ant* ant);

private:
    int m_Satiety;

protected:
    int         m_PheromoneTime;
    ImagoType   m_ImagoType;
};

