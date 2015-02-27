#include "TunnelManager.h"
#include "RoomScene.h"

#define MAX_DEEP -200
#define MIN_ROOM 4
#define MAX_INTERVAL 10

enum RoomType;
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
    //QueenRoom 1개 넣는 구간
    int yPosition = rand() % MAX_DEEP;
    m_RoomList[yPosition] = new RoomScene;
    m_RoomDeepList.push_back(yPosition);
    m_RoomList[yPosition]->SetRoomType(RT_QUEEN);

    //나머지 Room 넣는 구간
    for (int i = 0; i < roomNum; ++i)
    {
        int yPosition = rand() % MAX_DEEP;
        while (true)
        {
            if (CheckRoomInterval(yPosition))
            {
                m_RoomList[yPosition] = new RoomScene;
                m_RoomDeepList.push_back(yPosition);
                break;
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
