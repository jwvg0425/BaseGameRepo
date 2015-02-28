#include "Worker.h"

Worker::Worker(int x, int y)
{
    m_HP = 1500;
    m_STR = 200;
    m_INT = 100;
    m_Life = 500;
    m_ImagoType = IT_WORKER;
    m_X = x; m_Y = y;
}

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
    return Sprite::create("worker_1.png");
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
