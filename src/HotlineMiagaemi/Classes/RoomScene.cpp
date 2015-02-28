#include "RoomScene.h"
#include "StatWindow.h"
#include "GameManager.h"
#include "TunnelManager.h"
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
    m_MoveItem = createActButton("이동하기",
        CC_CALLBACK_1(RoomScene::moveCallback, this));
    setActButtonEnable(m_MoveItem, true);

    m_ActMenu = Menu::create(m_MoveItem, NULL);

    m_ActMenu->alignItemsHorizontallyWithPadding(30);
    m_ActMenu->setPosition(WND_WIDTH_GAME * 7 / 8, 50);

    addChild(m_ActMenu);
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
                break;
            }
            m_AntYPos--;
            break;
        case 1: //위로 향할 때
            if (m_AntYPos >= 0)
            {
                m_AntYPos--;
                break;
            }
            m_AntYPos++;
            break;
        case 2: //왼쪽으로 갈 때
            if (m_IsLeft) //왼쪽 방일경우 X좌표는 0~ -20
            {
                if (m_AntXPos <= m_SizeX)
                {
                    m_AntXPos++;
                    break;
                }
            }
            else //오른쪽 방일경우 X좌표는 0~ 20
            {
                if (m_AntXPos <= 0)
                {
                    m_AntXPos++;
                    break;
                }
            }
            m_AntXPos--;
            break;
        case 3: //오른쪽으로 갈 때
            if (m_IsLeft) //왼쪽 방일경우 X좌표는 0~ -20
            {
                if (m_AntXPos >= 0)
                {
                    m_AntXPos--;
                    break;
                }
            }
            else //오른쪽 방일경우 X좌표는 0~ 20
            {
                if (m_AntXPos >= m_SizeX)
                {
                    m_AntXPos--;
                    break;
                }
            }
            m_AntXPos++;
            break;
    }

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