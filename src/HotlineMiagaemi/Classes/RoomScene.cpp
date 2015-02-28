#include "RoomScene.h"
#include "StatWindow.h"
#include "GameManager.h"
#include "TunnelManager.h"
#include "Imago.h"
#include "Worker.h"
#include "Male.h"
#include "Soldier.h"
#include "Queen.h"
#include "const.h"

USING_NS_CC;

RoomScene::RoomScene()
{
}


RoomScene::~RoomScene()
{
}

cocos2d::Scene* RoomScene::createScene(RoomType roomType, bool isLeft, int sizeX, int sizeY)
{
    auto scene = Scene::create();

    auto layer = RoomScene::create();

    scene->addChild(layer);

    static_cast<RoomScene*>(layer)->setRoomType(roomType);
    static_cast<RoomScene*>(layer)->setRoomSizeX(sizeX);
    static_cast<RoomScene*>(layer)->setRoomSizeY(sizeY);

    return scene;
}

bool RoomScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    m_AntXPos = 0;
    m_AntYPos = 0;

    m_EggXPos = rand() % m_SizeX + 1;
    m_EggYPos = rand() % m_SizeY + 1;
    int antNum;
    if (m_RoomType == RT_QUEEN)
    {
        m_RoomAntList.push_back(GameManager::getInstance()->getQueen());
        GameManager::getInstance()->getQueen()->setPos(m_SizeX, m_SizeY);
        antNum = rand() % 5 + 10;
    }
    else
        antNum = rand() % 11 + 20;
    for (int i = 0; i < antNum; ++i)
    {
        while (true)
        {
            int x = rand() % m_SizeX + 1;
            int y = rand() % m_SizeY + 1;

            if (checkRoomAnt(x, y))
            {
                switch (m_RoomType)
                {
                case RT_NONE:
                    break;
                case RT_EGG:
                    m_RoomAntList.push_back(new Worker(x,y));
                    break;
                case RT_MALE:
                    m_RoomAntList.push_back(new Male(x,y));
                case RT_QUEEN:
                    m_RoomAntList.push_back(new Soldier(x, y));
                    break;
                }
                break;
            }
        }
    }
    m_MoveItem = createActButton("이동하기",
        CC_CALLBACK_1(RoomScene::moveCallback, this));
    setActButtonEnable(m_MoveItem, true);

    m_OutItem = createActButton("방 나가기",
        CC_CALLBACK_1(RoomScene::moveCallback, this));
    setActButtonEnable(m_OutItem, true);

    m_ActMenu = Menu::create(m_MoveItem, NULL);

    m_ActMenu->alignItemsHorizontallyWithPadding(30);
    m_ActMenu->setPosition(WND_WIDTH_GAME * 7 / 8, 50);

    addChild(m_ActMenu);
    return true;
}

bool RoomScene::checkRoomAnt(int x, int y)
{
    if (x == 0 && y == 0)
        return false;
    for (auto& ant : m_RoomAntList)
    {
        if (ant->getPosX() == x && ant->getPosY() == y)
            return false;
    }
    return true;
}

void RoomScene::moveCallback(cocos2d::Ref* ref)
{
    int dir = rand() % 4;
    switch (dir)
    {
        case 0: //아래로 향할 때
            if (m_SizeY >= m_AntYPos) //Y좌표는 최대 0~ -20
            {
                m_AntYPos++;
                if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                {
                    m_AntYPos--;
                }
                break;
            }
            m_AntYPos--;
            if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
            {
                m_AntYPos++;
            }
            break;
        case 1: //위로 향할 때
            if (m_AntYPos >= 0)
            {
                m_AntYPos--;
                if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                {
                    m_AntYPos++;
                }
                break;
            }
            m_AntYPos++;
            if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
            {
                m_AntYPos--;
            }
            break;
        case 2: //왼쪽으로 갈 때
            if (m_IsLeft) //왼쪽 방일경우 X좌표는 0~ -20
            {
                if (m_AntXPos <= m_SizeX)
                {
                    m_AntXPos++;
                    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                    {
                        m_AntXPos--;
                    }
                    break;
                }
            }
            else //오른쪽 방일경우 X좌표는 0~ 20
            {
                if (m_AntXPos <= 0)
                {
                    m_AntXPos++;
                    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                    {
                        m_AntXPos--;
                    }
                    break;
                }
            }
            m_AntXPos--;
            if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
            {
                m_AntXPos++;
            }
            break;
        case 3: //오른쪽으로 갈 때
            if (m_IsLeft) //왼쪽 방일경우 X좌표는 0~ -20
            {
                if (m_AntXPos >= 0)
                {
                    m_AntXPos--;
                    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                    {
                        m_AntXPos++;
                    }
                    break;
                }
            }
            else //오른쪽 방일경우 X좌표는 0~ 20
            {
                if (m_AntXPos >= m_SizeX)
                {
                    m_AntXPos--;
                    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                    {
                        m_AntXPos++;
                    }
                    break;
                }
            }
            m_AntXPos++;
            if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
            {
                m_AntXPos--;
            }
            break;
    }

    if (m_AntXPos == 0 && m_AntYPos == 0)
        setActButtonEnable(m_OutItem, true);
    else
        setActButtonEnable(m_OutItem, false);
}

void RoomScene::outCallback(cocos2d::Ref* ref)
{

}

cocos2d::MenuItem* RoomScene::createActButton(const std::string& labelText, ccMenuCallback callback)
{
    auto item = MenuItemImage::create("button.png", "button_pushed.png", callback);
    auto itemLabel = Label::createWithSystemFont(labelText, TEXT_FONT, 16);
    item->addChild(itemLabel);
    itemLabel->setPosition(36, 22);
    itemLabel->setColor(Color3B(0, 0, 0));

    return item;
}

void RoomScene::setActButtonEnable(cocos2d::MenuItem* item, bool enable)
{
    item->setEnabled(enable);

    if (enable)
    {
        item->setColor(Color3B(255, 255, 255));
    }
    else
    {
        item->setColor(Color3B(128, 128, 128));
    }
}


