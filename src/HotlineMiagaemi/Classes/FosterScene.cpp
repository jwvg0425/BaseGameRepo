#include "FosterScene.h"
#include "const.h"
#include "GameManager.h"
#include "Ant.h"
#include "Egg.h"

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

	//¸ÔÀÌ±â
	auto feedItem = createActButton("¸ÔÀÌ±â", 
		CC_CALLBACK_1(FosterScene::feedCallback,this));
	feedItem->setEnabled(false);
	feedItem->setColor(Color3B(128, 128, 128));
	//¼¼³ú½ÃÅ°±â
	auto brainwashItem = createActButton("¼¼³ú",
		CC_CALLBACK_1(FosterScene::brainwashCallback, this));
	brainwashItem->setEnabled(false);
	brainwashItem->setColor(Color3B(128, 128, 128));
	//ÈÆ·Ã½ÃÅ°±â
	auto trainItem = createActButton("ÈÆ·Ã", 
		CC_CALLBACK_1(FosterScene::trainCallback, this));
	trainItem->setEnabled(false);
	trainItem->setColor(Color3B(128, 128, 128));

	//ÀáÀÔ
	auto infiltrateItem = createActButton("ÀáÀÔ",
		CC_CALLBACK_1(FosterScene::infiltrateCallback, this));
	infiltrateItem->setEnabled(false);
	infiltrateItem->setColor(Color3B(128, 128, 128));

	m_ActMenu = Menu::create(feedItem, brainwashItem, trainItem, infiltrateItem, nullptr);

	m_ActMenu->alignItemsHorizontallyWithPadding(30);
	m_ActMenu->setPosition(WND_WIDTH_GAME/2, 50);

	addChild(m_ActMenu);

	m_AntSprite = GameManager::getInstance()->getAnt()->getSprite();
	addChild(m_AntSprite);

	m_AntSprite->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2);

	m_Gaugebar = Sprite::create("gaugebar.png");
	addChild(m_Gaugebar);

	m_Gaugebar->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2 - 64);

	m_Gauge = Sprite::create("gauge.png");
	m_Gauge->setScaleX(0);
	addChild(m_Gauge);

	m_Gauge->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2 - 64);

	scheduleUpdate();

    return true;
}

FosterScene::FosterScene() : m_ActMenu(nullptr), m_AntSprite(nullptr)
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

void FosterScene::update(float dTime)
{
	Ant* ant = GameManager::getInstance()->getAnt();

	ant->update(dTime);

	if (ant->isEvolve())
	{
		GameManager::getInstance()->setAnt(ant->evolve());
	}
}
