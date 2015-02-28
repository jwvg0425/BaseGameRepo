#include "HallScene.h"
#include "StatWindow.h"
#include "GameManager.h"
#include "TunnelManager.h"
#include "const.h"
#include "HallSprite.h"

USING_NS_CC;

HallScene::HallScene() : m_Sprite(nullptr)
{
}


HallScene::~HallScene()
{
}

Scene* HallScene::createScene()
{
    auto scene = Scene::create();

    auto layer = HallScene::create();

    scene->addChild(layer);

    return scene;
}

bool HallScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
    {
        return false;
    }
    m_AntXPos = 0;
    m_AntYPos = 0;

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    glview->setFrameSize(WND_WIDTH_GAME, WND_HEIGHT_GAME);
    glview->setDesignResolutionSize(WND_WIDTH_GAME, WND_HEIGHT_GAME, ResolutionPolicy::SHOW_ALL);

    m_DodgeItem = createActButton("회피하기",
        CC_CALLBACK_1(HallScene::dodgeCallback, this));
    setActButtonEnable(m_DodgeItem, true);

    m_MoveItem = createActButton("이동하기",
        CC_CALLBACK_1(HallScene::moveCallback, this));
    setActButtonEnable(m_MoveItem, true);

    m_EnterItem = createActButton("방 입장",
        CC_CALLBACK_1(HallScene::enterCallback, this));
    setActButtonEnable(m_EnterItem, false);

    m_ActMenu = Menu::create(m_DodgeItem, m_MoveItem, m_EnterItem, NULL);

    m_ActMenu->alignItemsHorizontallyWithPadding(30);
    m_ActMenu->setPosition(WND_WIDTH_GAME * 5 / 8, 50);

    addChild(m_ActMenu);

	m_Sprite = HallSprite::create();
	addChild(m_Sprite,-1);
    return true;
}

void HallScene::dodgeCallback(cocos2d::Ref* ref)
{
    int random = rand() % 3;

    switch (random)
    {
    case 0: //위로 갈 떄
        if (m_AntYPos == 0)
            break;
        m_AntYPos++;
        break;
    case 1: //왼쪽으로 갈 때
        if (m_AntXPos == -1)  //막혔을때 반대로 가거나 뒤로가기
        {
            random = rand() % 2;
            switch (random)
            {
            case 0:
                m_AntXPos++;
                break;
            case 1:
                m_AntYPos++;
                break;
            }
            break;
        }
        m_AntXPos--;
        break;
    case 2: //오른쪽으로 갈 때
        if (m_AntXPos == 1)
        {
            random = rand() % 2;
            switch (random)
            {
            case 0:
                m_AntXPos--;
                break;
            case 1:
                m_AntYPos++;
                break;
            }
            break;
        }
        m_AntXPos++;
        break;
    }
    if (TunnelManager::getInstance()->isRoomExist(m_AntXPos, m_AntYPos))
        setActButtonEnable(m_EnterItem, true);
    else
        setActButtonEnable(m_EnterItem, false);
}

void HallScene::moveCallback(cocos2d::Ref* ref)
{
    m_AntYPos--;
    if (TunnelManager::getInstance()->isRoomExist(m_AntXPos, m_AntYPos))
        setActButtonEnable(m_EnterItem, true);
    else
        setActButtonEnable(m_EnterItem, false);
}

void HallScene::enterCallback(cocos2d::Ref* ref)
{
    TunnelManager::getInstance()->roomSceneCallback(m_AntYPos);
}

cocos2d::MenuItem* HallScene::createActButton(const std::string& labelText, ccMenuCallback callback)
{
    auto item = MenuItemImage::create("button.png", "button_pushed.png", callback);
    auto itemLabel = Label::createWithSystemFont(labelText, TEXT_FONT, 16);
    item->addChild(itemLabel);
    itemLabel->setPosition(36, 22);
    itemLabel->setColor(Color3B(0, 0, 0));

    return item;
}

void HallScene::setActButtonEnable(cocos2d::MenuItem* item, bool enable)
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

int HallScene::getAntYPos()
{
	return m_AntYPos;
}

int HallScene::getAntXPos()
{
	return m_AntXPos;
}
