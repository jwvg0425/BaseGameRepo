#include "HallScene.h"
#include "StatWindow.h"
#include "GameManager.h"
#include "TunnelManager.h"
#include "const.h"
#include "HallSprite.h"
#include "FosterScene.h"
#include "StatWindow.h"

USING_NS_CC;

HallScene::HallScene() : m_Sprite(nullptr)
{
	m_IsAct = true;
	m_Time = 0;
}


HallScene::~HallScene()
{
}

cocos2d::Scene* HallScene::createScene(int playerX, int playerY)
{
    auto scene = Scene::create();

    auto layer = HallScene::create();

    scene->addChild(layer);

    static_cast<HallScene*>(layer)->setAntXPos(playerX);
    static_cast<HallScene*>(layer)->setAntYPos(playerY);

    return scene;
}

bool HallScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 0)))
    {
        return false;
    }

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

	scheduleUpdate();
    return true;
}

void HallScene::dodgeCallback(cocos2d::Ref* ref)
{
	if (!m_IsAct)
		return;

	m_IsAct = false;
	m_Time = 0;

	GameManager::getInstance()->getAnt()->addAge(1);
    int random = rand() % 3;

    switch (random)
    {
    case 0: //위로 갈 떄
        if (m_AntYPos == 0)
            break;
        m_AntYPos++;
		GameManager::getInstance()->getAnt()->setDir(DIR_UP);
        if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
        {
            m_AntYPos--;
        }
        break;
    case 1: //왼쪽으로 갈 때
        if (m_AntXPos == -1)  //막혔을때 반대로 가거나 뒤로가기
        {
            random = rand() % 2;
            switch (random)
            {
            case 0: //반대로 갈 때
                m_AntXPos++;
				GameManager::getInstance()->getAnt()->setDir(DIR_RIGHT);
                if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                {
                    m_AntXPos--;
                }
                break;
            case 1: //뒤로 갈 떄
                if (m_AntYPos == 0) //막혔을 때
                {
                    m_AntXPos++;
					GameManager::getInstance()->getAnt()->setDir(DIR_RIGHT);
                    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                    {
                        m_AntXPos--;
                    }
                    break;
                }
				GameManager::getInstance()->getAnt()->setDir(DIR_UP);
                m_AntYPos++;
                if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                {
                    m_AntYPos--;
                }
                break;
            }
            break;
        }
        m_AntXPos--;
		GameManager::getInstance()->getAnt()->setDir(DIR_LEFT);
        if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
        {
            m_AntXPos++;
        }
        break;
    case 2: //오른쪽으로 갈 때
        if (m_AntXPos == 1)
        {
            random = rand() % 2;
            switch (random)
            {
            case 0: //반대로 갈 때
                m_AntXPos--;
				GameManager::getInstance()->getAnt()->setDir(DIR_LEFT);
                if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                {
                    m_AntXPos++;
                }
                break;
            case 1: //뒤로 갈 때
                if (m_AntYPos == 0) // 막혔을 때
                {
                    m_AntXPos--;
					GameManager::getInstance()->getAnt()->setDir(DIR_LEFT);
                    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                    {
                        m_AntXPos++;
                    }
                    break;
                }
                m_AntYPos++;
				GameManager::getInstance()->getAnt()->setDir(DIR_UP);
                if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
                {
                    m_AntYPos--;
                }
                break;
            }
            break;
        }
        m_AntXPos++;
		GameManager::getInstance()->getAnt()->setDir(DIR_RIGHT);
        if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
        {
            m_AntXPos--;
        }
        break;
    }
    TunnelManager::getInstance()->moveCallback(m_AntXPos, m_AntYPos);
    if (TunnelManager::getInstance()->isRoomExist(m_AntXPos, m_AntYPos))
        setActButtonEnable(m_EnterItem, true);
    else
        setActButtonEnable(m_EnterItem, false);
}

void HallScene::moveCallback(cocos2d::Ref* ref)
{
	if (!m_IsAct)
		return;

	m_IsAct = false;
	m_Time = 0;

    m_AntYPos--;
	GameManager::getInstance()->getAnt()->addAge(1);
	GameManager::getInstance()->getAnt()->setDir(DIR_DOWN);
    if (m_AntYPos <= MAX_DEEP)
        m_AntYPos++;
    if (TunnelManager::getInstance()->isAntExist(m_AntXPos, m_AntYPos))
    {
        m_AntYPos++;
    }
    TunnelManager::getInstance()->moveCallback(m_AntXPos, m_AntYPos);
    if (TunnelManager::getInstance()->isRoomExist(m_AntXPos, m_AntYPos))
        setActButtonEnable(m_EnterItem, true);
    else
        setActButtonEnable(m_EnterItem, false);
}

void HallScene::enterCallback(cocos2d::Ref* ref)
{
	if (!m_IsAct)
		return;

	m_IsAct = false;
	m_Time = 0;

	GameManager::getInstance()->getAnt()->addAge(1);
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

void HallScene::update(float dTime)
{
	if (!m_IsAct)
	{
		m_Time += dTime;

		if (m_Time > 0.55f)
		{
			m_IsAct = true;
		}
	}

	if (GameManager::getInstance()->getAnt()->isDead())
	{
		GameManager::getInstance()->antDie();
		GameManager::getInstance()->initAnt();
		Director::getInstance()->replaceScene(FosterScene::createScene());
	}
	//죽은 애들 삭제 처리
	TunnelManager::getInstance()->updateHallAntList();
}
