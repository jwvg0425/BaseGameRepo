#include "Worker.h"


Worker::Worker()
{
    m_HP = 300;
    m_STR = 70;
    m_INT = 20;
    m_Life = 200;
    m_ImagoType = IT_WORKER;
}


Worker::~Worker()
{
}

Sprite* Worker::getSprite()
{
    return Sprite::create("worker.png");
}

bool Worker::isEvolve()
{
	return false;
}

Ant* Worker::evolve()
{
	return nullptr;
}

void Worker::update(float dTime)
{

}
