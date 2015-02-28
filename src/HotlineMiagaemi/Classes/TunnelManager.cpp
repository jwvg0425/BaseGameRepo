#include "TunnelManager.h"
#include "GameManager.h"
#include "HallScene.h"
#include "Ant.h"
#include "Imago.h"
#include "Worker.h"
#include "Male.h"
#include "Soldier.h"

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
    m_PlayerAnt = GameManager::getInstance()->getAnt();
    initRoom();
    initAnt();
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
            //Room의 사이즈설정
            Size roomSize;
            if (isLeft)
            {
                roomSize.x = -(rand() % 11 + 10);
                roomSize.y = -(rand() % 11 + 10);
            }
            else
            {
                roomSize.x = (rand() % 11 + 10);
                roomSize.y = -(rand() % 11 + 10);
            }
            //Room의 Type설정
            int random = rand() % 2;
            auto roomType = RT_NONE;
            switch (random)
            {
            case 0:
                roomType = RT_EGG;
                break;
            case 1:
                roomType = RT_MALE;
                break;
            }
            ///////////////////////////
            if (checkRoomInterval(yPosition))
            {
                m_RoomDirList[yPosition] = isLeft;
                m_RoomTypeList[yPosition] = roomType;
                m_RoomSizeList[yPosition] = roomSize;
                break;
            }
        }
    }
}

void TunnelManager::initAnt()
{
    int antNum = MIN_ANT + (rand() % MIN_ANT);
    for (int i = 0; i < antNum; ++i)
    {
        while (true)
        {
            int xPos = (rand() % 3) - 1;
            int yPos = -(rand() % MAX_DEEP);
            int antType = rand() % 100;
            Imago* ant;
            if (checkAntInterval(yPos))
            {
                if (antType < 50)
                {
                    ant = new Worker(xPos, yPos);
                    m_HallAntList.push_back(ant);
                }
                else if (antType < 80)
                {
                    ant = new Soldier(xPos, yPos);
                    m_HallAntList.push_back(ant);
                }
                else
                {
                    ant = new Male(xPos, yPos);
                    m_HallAntList.push_back(ant);
                }
                break;
                ant->setPos(xPos, yPos);
            }
        }
    }
}

bool TunnelManager::checkRoomInterval(int yPosition)
{
    for (auto& roomDeep : m_RoomDirList)
    {
        if (yPosition <= roomDeep.first + MAX_ROOM_INTERVAL &&
            yPosition >= roomDeep.first - MAX_ROOM_INTERVAL)
            return false;
    }
    return true;
}

bool TunnelManager::checkAntInterval(int antYPos)
{
    if (antYPos == 0)
        return false;

    for (auto& ant : m_HallAntList)
    {
        if (antYPos == ant->getPosY())
            return false;
    }
    return true;
}

void TunnelManager::moveCallback(int playerX, int playerY)
{
    for (auto& ant : m_HallAntList)
    {
        int prevX = ant->getPosX();
        int prevY = ant->getPosY();
        ant->move();
        //ai가 움직였을 때 player와 겹치는 경우를 테스트
        if (playerX == ant->getPosX() && playerY == ant->getPosY())
        {
            ant->attack(m_PlayerAnt);
            ant->setPos(prevX, prevY);
        }

        //AI Ant들끼리 겹치는 경우를 테스트
        for (auto& otherAnt : m_HallAntList)
        {
            if (ant == otherAnt)
                continue;
            if (ant->getPosX() == otherAnt->getPosX() &&
                ant->getPosY() == otherAnt->getPosY())
            {
                ant->setPos(prevX, prevY);
            }
        }
    }
}

void TunnelManager::hallSceneCallback(Ref* sender)
{
    Director::getInstance()->replaceScene(HallScene::createScene());
}

void TunnelManager::roomSceneCallback(int antYPos)
{
    for (auto& room : m_RoomTypeList)
    {
        if (room.first == antYPos)
        {
            auto roomSize = m_RoomSizeList[antYPos];
            auto isLeft = m_RoomDirList[antYPos];
            Director::getInstance()->replaceScene(RoomScene::createScene(room.second, isLeft, roomSize.x, roomSize.y));
            return;
        }
    }
}

bool TunnelManager::isAntExist(int playerX, int playerY)
{
    for (auto& ant : m_HallAntList)
    {
        if (playerX == ant->getPosX() && playerY == ant->getPosY())
        {
            ant->isAttacked(m_PlayerAnt->getStr());
            return true;
        }
    }
    return false;
}

bool TunnelManager::isRoomExist(int antXPos, int antYPos)
{
    if (antXPos == 0)
        return false;

    for (auto& roomDeep : m_RoomDirList)
    {
		if (roomDeep.first == antYPos)
		{
			if (roomDeep.second == true && antXPos == -1)
				return true;
			else if (roomDeep.second == false && antXPos == 1)
				return true;
			else
				return false;
		}
    }
    return false;
}

const std::vector<Imago*>& TunnelManager::getHallAntList()
{
	return m_HallAntList;
}
