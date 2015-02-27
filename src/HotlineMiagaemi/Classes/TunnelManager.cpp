#include "TunnelManager.h"

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
    initRoom();
    m_AntDeep = 0;
}


TunnelManager::~TunnelManager()
{
}

void TunnelManager::initRoom()
{
    int roomNum = MIN_ROOM + rand() % MIN_ROOM;
    //QueenRoom 1�� �ִ� ����
    int yPosition = rand() % MAX_DEEP;

    //������ Room �ִ� ����
    for (int i = 0; i < roomNum; ++i)
    {
        while (true)
        {
            int yPosition = rand() % MAX_DEEP;  //Room�� ���̼���
            auto isLeft = (rand() % 2) ? true : false; //Room�� ���⼳��
            //Room�� Type����
            int random = rand() % 2;
            auto roomType = RT_NONE;
            switch (random)
            {
            case 0:
                roomType = RT_EGG;
            case 1:
                roomType = RT_PRINCESS;
            }
            ///////////////////////////
            if (CheckRoomInterval(yPosition))
            {
                m_RoomDirList[yPosition] = isLeft;
                m_RoomTypeList[yPosition] = roomType;
                break;
            }
        }
    }
}

bool TunnelManager::CheckRoomInterval(int yPosition)
{
    for (auto& roomDeep : m_RoomDirList)
    {
        if (yPosition <= roomDeep.first + MAX_INTERVAL &&
            yPosition >= roomDeep.first - MAX_INTERVAL)
            return false;
    }
    return true;
}
