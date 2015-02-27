#include "PrincessRoom.h"
#include "stdlib.h"

PrincessRoom::PrincessRoom()
{
    m_IsLeft = (rand() % 2) ? true : false;
}


PrincessRoom::~PrincessRoom()
{
}
