#include "HallScene.h"
#include "StatWindow.h"
#include "GameManager.h"
#include "TunnelManager.h"
#include "const.h"

USING_NS_CC;

HallScene::HallScene()
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
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    m_AntPos = 0;

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    glview->setFrameSize(WND_WIDTH_GAME, WND_HEIGHT_GAME);
    glview->setDesignResolutionSize(WND_WIDTH_GAME, WND_HEIGHT_GAME, ResolutionPolicy::SHOW_ALL);

    m_MoveItem = createActButton("이동하기",
        CC_CALLBACK_1(HallScene::moveCallback, this));
    setActButtonEnable(m_MoveItem, true);

    //세뇌시키기
    m_EnterItem = createActButton("방 입장",
        CC_CALLBACK_1(HallScene::enterCallback, this));
    setActButtonEnable(m_EnterItem, false);

    m_ActMenu = Menu::create(m_MoveItem, m_EnterItem, NULL);

    m_ActMenu->alignItemsHorizontallyWithPadding(30);
    m_ActMenu->setPosition(WND_WIDTH_GAME * 3 / 4, 50);

    addChild(m_ActMenu);
    return true;
}

void HallScene::moveCallback(cocos2d::Ref* ref)
{
    m_AntPos--;
    if(TunnelManager::getInstance()->isRoomExist(m_AntPos))
        setActButtonEnable(m_EnterItem, true);
}

void HallScene::enterCallback(cocos2d::Ref* ref)
{

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