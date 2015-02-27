#include "FosterScene.h"
#include "const.h"

USING_NS_CC;

Scene* FosterScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = FosterScene::create();

    scene->addChild(layer);

    return scene;
}
bool FosterScene::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	glview->setFrameSize(WND_WIDTH_GAME, WND_HEIGHT_GAME);
	glview->setDesignResolutionSize(WND_WIDTH_GAME, WND_HEIGHT_GAME, ResolutionPolicy::SHOW_ALL);

	//���̱�
	auto feedItem = createActButton("���̱�", 
		CC_CALLBACK_1(FosterScene::feedCallback,this));
	//������Ű��
	auto brainwashItem = createActButton("����",
		CC_CALLBACK_1(FosterScene::brainwashCallback, this));
	//�Ʒý�Ű��
	auto trainItem = createActButton("�Ʒ�", 
		CC_CALLBACK_1(FosterScene::trainCallback, this));
	//����
	auto infiltrateItem = createActButton("����",
		CC_CALLBACK_1(FosterScene::infiltrateCallback, this));

	m_ActMenu = Menu::create(feedItem, brainwashItem, trainItem, infiltrateItem, nullptr);

	m_ActMenu->alignItemsHorizontallyWithPadding(30);
	m_ActMenu->setPosition(WND_WIDTH_GAME/2, 50);

	addChild(m_ActMenu);

    return true;
}

FosterScene::FosterScene() : m_ActMenu(nullptr)
{

}

FosterScene::~FosterScene()
{

}

cocos2d::MenuItem* FosterScene::createActButton(const std::string& labelText, ccMenuCallback callback)
{
	auto item = MenuItemImage::create("button.png", "button_pushed.png", callback);
	auto itemLabel = Label::createWithSystemFont(labelText, TEXT_FONT, 16);
	item->addChild(itemLabel);
	itemLabel->setPosition(36, 22);
	itemLabel->setColor(Color3B(0, 0, 0));

	return item;
}

void FosterScene::feedCallback(cocos2d::Ref* ref)
{

}

void FosterScene::brainwashCallback(cocos2d::Ref* ref)
{

}

void FosterScene::trainCallback(cocos2d::Ref* ref)
{

}

void FosterScene::infiltrateCallback(cocos2d::Ref* ref)
{

}
