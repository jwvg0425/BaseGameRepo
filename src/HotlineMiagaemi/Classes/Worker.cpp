#include "Worker.h"


Worker::Worker()
{
    m_HP = 300;
    m_STR = 70;
    m_INT = 20;
}


Worker::~Worker()
{
}

Sprite* Worker::getSprite()
{
    return Sprite::create("worker.png");
}
