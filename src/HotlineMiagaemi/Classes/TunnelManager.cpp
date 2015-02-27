#include "TunnelManager.h"
#include "EggRoom.h"
#include "PrincessRoom.h"
#include "QueenRoom.h"
#include "Room.h"

#define MAX_DEEP -200
#define MIN_ROOM 4
#define MAX_INTERVAL 10

TunnelManager* TunnelManager::m_Instance = nullptr;

TunnelManager* TunnelManager::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new TunnelManager;
    }

    return m_Instance;
}

void TunnelManager::releaseInstance()
{
    if (m_Instance != nullptr)
    {
        delete m_Instance;
        m_Instance = nullptr;
    }
}

TunnelManager::TunnelManager()
{
}


TunnelManager::~TunnelManager()
{
}

void TunnelManager::initRoom()
{
    int roomNum = MIN_ROOM + rand() % MIN_ROOM;
    //QueenRoom 넣는 구간
    int yPosition = rand() % MAX_DEEP;
    m_RoomList[yPosition] = new QueenRoom;
    m_RoomDeepList.push_back(yPosition);

    for (int i = 0; i < roomNum; ++i)
    {
        int roomType = rand() % 3;
        int yPosition = rand() % MAX_DEEP;
        while (true)
        {
            if (CheckRoomInterval(yPosition))
            {
                switch (roomType)
                {
                case 0:
                    m_RoomList[yPosition] = new EggRoom;
                    break;
                case 1:
                    m_RoomList[yPosition] = new PrincessRoom;
                    break;
                default:
                    break;
                }
                m_RoomDeepList.push_back(yPosition);
            }
            yPosition = rand() % MAX_DEEP;
        }
    }
}

bool TunnelManager::CheckRoomInterval(int yPosition)
{
    for (auto& roomDeep : m_RoomDeepList)
    {
        if (yPosition <= roomDeep + MAX_INTERVAL &&
            yPosition >= roomDeep - MAX_INTERVAL)
            return false;
    }
    return true;
}
