#include "FosterScene.h"
#include "const.h"
#include "GameManager.h"
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

	//먹이기
	m_FeedItem = createActButton("먹이기", 
		CC_CALLBACK_1(FosterScene::feedCallback,this));
	setActButtonEnable(m_FeedItem, false);

	//세뇌시키기
	m_BrainWashItem = createActButton("세뇌",
		CC_CALLBACK_1(FosterScene::brainwashCallback, this));
	setActButtonEnable(m_BrainWashItem, false);
	//훈련시키기
	m_TrainItem = createActButton("훈련", 
		CC_CALLBACK_1(FosterScene::trainCallback, this));
	setActButtonEnable(m_TrainItem, false);

	//잠입
	m_InfiltrateItem = createActButton("잠입",
		CC_CALLBACK_1(FosterScene::infiltrateCallback, this));
	setActButtonEnable(m_InfiltrateItem, false);

	m_ActMenu = Menu::create(m_FeedItem, m_BrainWashItem, m_TrainItem, m_InfiltrateItem, nullptr);

	m_ActMenu->alignItemsHorizontallyWithPadding(30);
	m_ActMenu->setPosition(WND_WIDTH_GAME/2, 50);

	addChild(m_ActMenu);

	m_AntSprite = GameManager::getInstance()->getAnt()->getSprite();
	addChild(m_AntSprite);

	m_AntSprite->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2);

	m_Gaugebar = Sprite::create("gaugebar.png");
	m_Gaugebar->setAnchorPoint(Point(0, 0));
	addChild(m_Gaugebar);

	m_Gaugebar->setPosition(WND_WIDTH_GAME / 2 - 32, WND_HEIGHT_GAME / 2 - 96);

	m_Gauge = Sprite::create("gauge.png");
	m_Gauge->setAnchorPoint(Point(0, 0));
	addChild(m_Gauge);

	m_Gauge->setPosition(WND_WIDTH_GAME / 2 - 32, WND_HEIGHT_GAME / 2 - 96);

	//TODO : 함수 받아서 action 종료시에 해당 함수 실행할 수 있게.
	startAction(Egg::getEvolveTime(), nullptr);

	scheduleUpdate();

    return true;
}

FosterScene::FosterScene() : m_ActMenu(nullptr), m_AntSprite(nullptr), m_BrainWashItem(nullptr),
m_FeedItem(nullptr),m_Gaugebar(nullptr),m_Gauge(nullptr),m_InfiltrateItem(nullptr),m_TrainItem(nullptr),
m_ActTime(0.0f), m_CompleteTime(0.0f), m_IsAct(false), m_CompleteActionFunc(nullptr)
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
	if (!m_IsAct)
	{
		startAction(1.0f, std::bind(&FosterScene::feedComplete, this));
	}
}

void FosterScene::brainwashCallback(cocos2d::Ref* ref)
{
	if (!m_IsAct)
	{
		startAction(1.0f, nullptr);
	}
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
		Ant* evolveAnt = ant->evolve();
		m_AntSprite->removeFromParent();
		m_AntSprite = evolveAnt->getSprite();
		m_AntSprite->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2);
		addChild(m_AntSprite);
		
		auto animation = GameManager::getInstance()->getAnimation(evolveAnt);

		if (animation != nullptr)
		{
			auto ani = RepeatForever::create(Animate::create(animation));

			m_AntSprite->runAction(ani);
		}

		GameManager::getInstance()->setAnt(evolveAnt);

		setActButtonEnable(m_FeedItem, evolveAnt->isFeed());
		setActButtonEnable(m_BrainWashItem, evolveAnt->isBrainwash());
		setActButtonEnable(m_TrainItem, evolveAnt->isTrain());
		setActButtonEnable(m_InfiltrateItem, evolveAnt->isInfiltrate());
	}

	if (m_IsAct)
	{
		m_ActTime += dTime;

		updateGauge();

		if (m_ActTime > m_CompleteTime)
		{
			completeAction();
		}
	}
}

void FosterScene::setActButtonEnable(cocos2d::MenuItem* item, bool enable)
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

void FosterScene::startAction(float completeTime, ActionFunc completeActionFunc)
{
	m_CompleteActionFunc = completeActionFunc;
	m_CompleteTime = completeTime;
	m_IsAct = true;
	m_ActTime = 0.0f;
	m_Gaugebar->setVisible(true);
	m_Gauge->setVisible(true);
	m_Gauge->setScaleX(0.0f);
}

void FosterScene::completeAction()
{
	m_IsAct = false;
	m_Gaugebar->setVisible(false);
	m_Gauge->setVisible(false);

	if (m_CompleteActionFunc != nullptr)
	{
		m_CompleteActionFunc();
	}
}

void FosterScene::updateGauge()
{
	float ratio = m_ActTime / m_CompleteTime;

	if (ratio > 1.0f)
	{
		ratio = 1.0f;
	}
	m_Gauge->setScaleX(ratio);
}

void FosterScene::feedComplete()
{
	GameManager::getInstance()->getAnt()->addSatiety(10);
}
