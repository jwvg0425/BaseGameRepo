#include "EggRoom.h"
#include "stdlib.h"

EggRoom::EggRoom()
{
    m_IsLeft = (rand() % 2) ? true : false;
}


EggRoom::~EggRoom()
{
}
