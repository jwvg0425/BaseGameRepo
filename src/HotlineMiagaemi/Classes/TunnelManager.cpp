#include "TunnelManager.h"
#include "HallScene.h"

#define MAX_DEEP 200
#define MIN_ROOM 4
#define MAX_INTERVAL 10

USING_NS_CC;

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
}


TunnelManager::~TunnelManager()
{
}

void TunnelManager::initRoom()
{
    int roomNum = MIN_ROOM + rand() % MIN_ROOM;
    //QueenRoom 1개 넣는 구간
    int yPosition = rand() % MAX_DEEP;

    //나머지 Room 넣는 구간
    for (int i = 0; i < roomNum; ++i)
    {
        while (true)
        {
            int yPosition = -(rand() % MAX_DEEP);  //Room의 깊이설정
            auto isLeft = (rand() % 2) ? true : false; //Room의 방향설정
            //Room의 Type설정
            int random = rand() % 2;
            auto roomType = RT_NONE;
            switch (random)
            {
            case 0:
                roomType = RT_EGG;
                break;
            case 1:
                roomType = RT_PRINCESS;
                break;
            }
            ///////////////////////////
            if (checkRoomInterval(yPosition))
            {
                m_RoomDirList[yPosition] = isLeft;
                m_RoomTypeList[yPosition] = roomType;
                break;
            }
        }
    }
}

bool TunnelManager::checkRoomInterval(int yPosition)
{
    for (auto& roomDeep : m_RoomDirList)
    {
        if (yPosition <= roomDeep.first + MAX_INTERVAL &&
            yPosition >= roomDeep.first - MAX_INTERVAL)
            return false;
    }
    return true;
}

void TunnelManager::hallSceneCallback(Ref* sender)
{
    Director::getInstance()->replaceScene(HallScene::createScene());
}

void TunnelManager::roomSceneCallback(int antPos)
{
    for (auto& room : m_RoomTypeList)
    {
        if (room.first == antPos)
        {
            Director::getInstance()->replaceScene(RoomScene::createScene(room.second));
            return;
        }
    }
}

bool TunnelManager::isRoomExist(int antPos)
{
    for (auto& roomDeep : m_RoomDirList)
    {
        if (roomDeep.first == antPos)
            return true;
    }
    return false;
}
