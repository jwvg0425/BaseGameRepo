#include "QueenRoom.h"
#include "stdlib.h"

QueenRoom::QueenRoom()
{
    m_IsLeft = (rand() % 2) ? true : false;
}


QueenRoom::~QueenRoom()
{
}
