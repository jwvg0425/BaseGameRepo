#include "FosterScene.h"
#include "const.h"
#include "GameManager.h"
#include "TunnelManager.h"
#include "StatWindow.h"
#include "Egg.h"
#include "Imago.h"

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

	//훈련 메뉴
	auto battleItem = createActButton("전투 훈련",
		CC_CALLBACK_1(FosterScene::battleCallback, this));
	setActButtonEnable(battleItem, true);

	auto athleticItem = createActButton("체력 훈련",
		CC_CALLBACK_1(FosterScene::athleticCallback, this));
	setActButtonEnable(athleticItem, true);

	auto exploreItem = createActButton("탐사 훈련",
		CC_CALLBACK_1(FosterScene::exploreCallback, this));
	setActButtonEnable(battleItem, true);

	auto dodgeItem = createActButton("회피 훈련",
		CC_CALLBACK_1(FosterScene::dodgeCallback, this));
	setActButtonEnable(dodgeItem, true);

	auto hellItem = createActButton("지옥",
		CC_CALLBACK_1(FosterScene::hellCallback, this));
	setActButtonEnable(hellItem, true);

	m_TrainMenu = Menu::create(battleItem, athleticItem, exploreItem, dodgeItem, hellItem, nullptr);
	m_TrainMenu->alignItemsVerticallyWithPadding(5);
	m_TrainMenu->setPosition(WND_WIDTH_GAME / 2 - 144, WND_HEIGHT_GAME / 2);
	m_TrainMenu->setVisible(m_IsTrainVisible);

	addChild(m_TrainMenu);

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

	m_StatWindow = StatWindow::create();
	m_StatWindow->setPosition(WND_WIDTH_GAME / 2 + 160, WND_HEIGHT_GAME / 2);
	addChild(m_StatWindow);

	m_TypeLabel = Label::createWithSystemFont("알", TEXT_FONT, 16);
	addChild(m_TypeLabel);
	m_TypeLabel->setAnchorPoint(Point(0.5, 0.5));
	m_TypeLabel->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2 - 128);
	m_TypeLabel->setColor(Color3B(0, 0, 0));

	auto sprite = Sprite::create("egg_interface.png");
	sprite->setPosition(10, WND_HEIGHT_GAME - 80);
	sprite->setAnchorPoint(Point(0, 0));
	addChild(sprite);

	m_EggNum = Label::createWithSystemFont("5", TEXT_FONT, 64);
	m_EggNum->setColor(Color3B(0, 0, 0));
	m_EggNum->setPosition(132, 0);
	m_EggNum->setAnchorPoint(Point(0, 0));
	sprite->addChild(m_EggNum);

	startAction(Egg::getEvolveTime(), nullptr);

	scheduleUpdate();

    return true;
}

FosterScene::FosterScene() : m_ActMenu(nullptr), m_AntSprite(nullptr), m_BrainWashItem(nullptr),
m_FeedItem(nullptr), m_Gaugebar(nullptr), m_Gauge(nullptr), m_InfiltrateItem(nullptr), m_TrainItem(nullptr), m_TrainMenu(nullptr),
m_TypeLabel(nullptr), m_ActTime(0.0f), m_CompleteTime(0.0f), m_IsAct(false),
m_CompleteActionFunc(nullptr), m_StatWindow(nullptr), m_EggNum(nullptr), m_IsTrainVisible(false)
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
		auto ant = GameManager::getInstance()->getAnt();
		auto type = ant->getType();

		switch (type)
		{
		case Ant::ST_LARVA:
		{
			auto animation = GameManager::createAnimation("larva_feed_%d.png", 1, 8, 0.125f);
			auto animate = Animate::create(animation);
			auto repeat = RepeatForever::create(animate);
			m_AntSprite->stopAllActions();
			m_AntSprite->runAction(repeat);
			startAction(2.0f, std::bind(&FosterScene::feedComplete, this));
			break;
		}
		case Ant::ST_IMAGO:
			switch (static_cast<Imago*>(ant)->getImagoType())
			{
			case Imago::IT_WORKER:
			{
				auto animation = GameManager::createAnimation("worker_feed_%d.png", 1, 8, 0.125f);
				auto animate = Animate::create(animation);
				auto repeat = RepeatForever::create(animate);
				m_AntSprite->stopAllActions();
				m_AntSprite->runAction(repeat);
				startAction(2.0f, std::bind(&FosterScene::feedComplete, this));
				break;
			}
			case Imago::IT_SOLDIER:
			{
				auto animation = GameManager::createAnimation("soldier_feed_%d.png", 1, 8, 0.125f);
				auto animate = Animate::create(animation);
				auto repeat = RepeatForever::create(animate);
				m_AntSprite->stopAllActions();
				m_AntSprite->runAction(repeat);
				startAction(2.0f, std::bind(&FosterScene::feedComplete, this));
				break;
			}
			}
		}
	}
}

void FosterScene::brainwashCallback(cocos2d::Ref* ref)
{
	if (!m_IsAct)
	{
		auto ant = GameManager::getInstance()->getAnt();
		auto type = ant->getType();

		switch (type)
		{
		case Ant::ST_LARVA:
		{
			auto animation = GameManager::createAnimation("larva_brainwash_%d.png", 1, 4, 0.2f);
			auto animate = Animate::create(animation);
			auto repeat = RepeatForever::create(animate);
			m_AntSprite->stopAllActions();
			m_AntSprite->runAction(repeat);
			
			auto label = Label::createWithSystemFont("개미를 죽입시다 개미는 나의 원수", TEXT_FONT, 16);
			label->setColor(Color3B(0, 0, 0));
			addChild(label);
			auto move = MoveBy::create(1.0f, Point(0, 60));
			auto fade = FadeOut::create(1.0f);
			auto spawn = Spawn::create(move, fade, nullptr);
			auto del = CallFunc::create(CC_CALLBACK_0(Label::removeFromParent, label));
			auto sequence = Sequence::create(spawn, del, nullptr);

			label->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2 + 64);
			label->runAction(sequence);
			startAction(2.0f, std::bind(&FosterScene::brainwashComplete, this));
			break;
		}
		case Ant::ST_IMAGO:
			switch (static_cast<Imago*>(ant)->getImagoType())
			{
			case Imago::IT_WORKER:
			{
				auto animation = GameManager::createAnimation("worker_brainwash_%d.png", 1, 4, 0.2f);
				auto animate = Animate::create(animation);
				auto repeat = RepeatForever::create(animate);
				m_AntSprite->stopAllActions();
				m_AntSprite->runAction(repeat);
				break;
			}
			case Imago::IT_SOLDIER:
			{
				auto animation = GameManager::createAnimation("soldier_brainwash_%d.png", 1, 4, 0.2f);
				auto animate = Animate::create(animation);
				auto repeat = RepeatForever::create(animate);
				m_AntSprite->stopAllActions();
				m_AntSprite->runAction(repeat);
				break;
			}
			}

			auto label = Label::createWithSystemFont("여왕 개미를 암살하라!", TEXT_FONT, 16);
			label->setColor(Color3B(0, 0, 0));
			addChild(label);
			auto move = MoveBy::create(1.0f, Point(0, 60));
			auto fade = FadeOut::create(1.0f);
			auto spawn = Spawn::create(move, fade, nullptr);
			auto del = CallFunc::create(CC_CALLBACK_0(Label::removeFromParent, label));
			auto sequence = Sequence::create(spawn, del, nullptr);

			label->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2 + 64);
			label->runAction(sequence);
			startAction(2.0f, std::bind(&FosterScene::brainwashComplete, this));
			break;
		}
	}
}

void FosterScene::trainCallback(cocos2d::Ref* ref)
{
	m_IsTrainVisible = !m_IsTrainVisible;

	m_TrainMenu->setVisible(m_IsTrainVisible);
}

void FosterScene::infiltrateCallback(cocos2d::Ref* ref)
{
    if (!m_IsAct)
    {
        TunnelManager::getInstance()->hallSceneCallback(ref);
    }
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

		switch (evolveAnt->getType())
		{
		case Ant::ST_LARVA:
			m_TypeLabel->setString("유충");
			break;
		case Ant::ST_IMAGO:
			switch (static_cast<Imago*>(evolveAnt)->getImagoType())
			{
			case Imago::IT_WORKER:
				m_TypeLabel->setString("일개미");
				break;
			case Imago::IT_SOLDIER:
				m_TypeLabel->setString("병정개미");
				break;
			case Imago::IT_PRINCESS:
				m_TypeLabel->setString("공주개미");
				break;
			case Imago::IT_MALE:
				m_TypeLabel->setString("수개미");
				break;
			}
			break;
		}
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

	m_StatWindow->update(dTime);
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
	GameManager::getInstance()->getAnt()->addSatiety(5 + (rand() % 5));
	GameManager::getInstance()->getAnt()->addAge(1);

	auto ant = GameManager::getInstance()->getAnt();
	auto type = ant->getType();

	switch (type)
	{
	case Ant::ST_LARVA:
	{
		auto animation = GameManager::createAnimation("larva_%d.png", 1, 2, 0.3f);
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);
		m_AntSprite->stopAllActions();
		m_AntSprite->runAction(repeat);
		break;
	}
	case Ant::ST_IMAGO:
		switch (static_cast<Imago*>(ant)->getImagoType())
		{
		case Imago::IT_WORKER:
		{
			auto animation = GameManager::createAnimation("worker_%d.png", 1, 4, 0.3f);
			auto animate = Animate::create(animation);
			auto repeat = RepeatForever::create(animate);
			m_AntSprite->stopAllActions();
			m_AntSprite->runAction(repeat);
			break;
		}
		case Imago::IT_SOLDIER:
		{
			auto animation = GameManager::createAnimation("soldier_%d.png", 1, 4, 0.3f);
			auto animate = Animate::create(animation);
			auto repeat = RepeatForever::create(animate);
			m_AntSprite->stopAllActions();
			m_AntSprite->runAction(repeat);
			break;
		}
		}
	}
}

void FosterScene::brainwashComplete()
{
	GameManager::getInstance()->getAnt()->addInt(1 + (rand() % 4));
	GameManager::getInstance()->getAnt()->addSatiety(-5 - (rand() % 5));
	GameManager::getInstance()->getAnt()->addAge(1 + (rand() % 3));
	auto ant = GameManager::getInstance()->getAnt();
	auto type = ant->getType();

	switch (type)
	{
	case Ant::ST_LARVA:
	{
		auto animation = GameManager::createAnimation("larva_%d.png", 1, 2, 0.3f);
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);
		m_AntSprite->stopAllActions();
		m_AntSprite->runAction(repeat);
		break;
	}
	case Ant::ST_IMAGO:
		switch (static_cast<Imago*>(ant)->getImagoType())
		{
		case Imago::IT_WORKER:
		{
			auto animation = GameManager::createAnimation("worker_%d.png", 1, 4, 0.3f);
			auto animate = Animate::create(animation);
			auto repeat = RepeatForever::create(animate);
			m_AntSprite->stopAllActions();
			m_AntSprite->runAction(repeat);
			break;
		}
		case Imago::IT_SOLDIER:
		{
			auto animation = GameManager::createAnimation("soldier_%d.png", 1, 4, 0.3f);
			auto animate = Animate::create(animation);
			auto repeat = RepeatForever::create(animate);
			m_AntSprite->stopAllActions();
			m_AntSprite->runAction(repeat);
			break;
		}
		}
	}
}

void FosterScene::battleCallback(cocos2d::Ref* sender)
{

}

void FosterScene::athleticCallback(cocos2d::Ref* sender)
{

}

void FosterScene::exploreCallback(cocos2d::Ref* sender)
{

}

void FosterScene::dodgeCallback(cocos2d::Ref* sender)
{

}

void FosterScene::hellCallback(cocos2d::Ref* sender)
{

}
