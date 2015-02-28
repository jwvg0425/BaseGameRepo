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

	//���̱�
	m_FeedItem = createActButton("���̱�", 
		CC_CALLBACK_1(FosterScene::feedCallback,this));
	setActButtonEnable(m_FeedItem, false);

	//������Ű��
	m_BrainWashItem = createActButton("����",
		CC_CALLBACK_1(FosterScene::brainwashCallback, this));
	setActButtonEnable(m_BrainWashItem, false);
	//�Ʒý�Ű��
	m_TrainItem = createActButton("�Ʒ�", 
		CC_CALLBACK_1(FosterScene::trainCallback, this));
	setActButtonEnable(m_TrainItem, false);

	//�Ʒ� �޴�
	auto battleItem = createActButton("���� �Ʒ�",
		CC_CALLBACK_1(FosterScene::battleCallback, this));
	setActButtonEnable(battleItem, true);

	auto athleticItem = createActButton("ü�� �Ʒ�",
		CC_CALLBACK_1(FosterScene::athleticCallback, this));
	setActButtonEnable(athleticItem, true);

	auto exploreItem = createActButton("Ž�� �Ʒ�",
		CC_CALLBACK_1(FosterScene::exploreCallback, this));
	setActButtonEnable(battleItem, true);

	auto dodgeItem = createActButton("ȸ�� �Ʒ�",
		CC_CALLBACK_1(FosterScene::dodgeCallback, this));
	setActButtonEnable(dodgeItem, true);

	auto hellItem = createActButton("���� �Ʒ�",
		CC_CALLBACK_1(FosterScene::hellCallback, this));
	setActButtonEnable(hellItem, true);

	m_TrainMenu = Menu::create(battleItem, athleticItem, exploreItem, dodgeItem, hellItem, nullptr);
	m_TrainMenu->alignItemsVerticallyWithPadding(5);
	m_TrainMenu->setPosition(WND_WIDTH_GAME / 2 - 144, WND_HEIGHT_GAME / 2);
	m_TrainMenu->setVisible(m_IsTrainVisible);

	addChild(m_TrainMenu);

	//����
	m_InfiltrateItem = createActButton("����",
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

	m_TypeLabel = Label::createWithSystemFont("��", TEXT_FONT, 16);
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
			runAnimation(m_AntSprite, GameManager::createAnimation("larva_feed_%d.png", 1, 8, 0.125f));
			startAction(2.0f, std::bind(&FosterScene::feedComplete, this));
			break;
		case Ant::ST_IMAGO:
			switch (static_cast<Imago*>(ant)->getImagoType())
			{
			case Imago::IT_WORKER:
				runAnimation(m_AntSprite, GameManager::createAnimation("worker_feed_%d.png", 1, 8, 0.125f));
				startAction(2.0f, std::bind(&FosterScene::feedComplete, this));
				break;
			case Imago::IT_SOLDIER:
				runAnimation(m_AntSprite, GameManager::createAnimation("soldier_feed_%d.png", 1, 8, 0.125f));
				startAction(2.0f, std::bind(&FosterScene::feedComplete, this));
				break;
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
			runAnimation(m_AntSprite, GameManager::createAnimation("larva_brainwash_%d.png", 1, 4, 0.2f));
			addUpmoveLabel(1, "���̸� ���Խô� ���̴� ���� ����", 60);

			startAction(2.0f, std::bind(&FosterScene::brainwashComplete, this));
			break;
		case Ant::ST_IMAGO:
			switch (static_cast<Imago*>(ant)->getImagoType())
			{
			case Imago::IT_WORKER:
				runAnimation(m_AntSprite, GameManager::createAnimation("worker_brainwash_%d.png", 1, 4, 0.2f));
				break;
			case Imago::IT_SOLDIER:
				runAnimation(m_AntSprite, GameManager::createAnimation("soldier_brainwash_%d.png", 1, 4, 0.2f));
				break;
			}

			addUpmoveLabel(1, "���� ���̸� �ϻ��϶�!", 60);
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
			m_TypeLabel->setString("����");
			break;
		case Ant::ST_IMAGO:
			switch (static_cast<Imago*>(evolveAnt)->getImagoType())
			{
			case Imago::IT_WORKER:
				m_TypeLabel->setString("�ϰ���");
				break;
			case Imago::IT_SOLDIER:
				m_TypeLabel->setString("��������");
				break;
			case Imago::IT_PRINCESS:
				m_TypeLabel->setString("���ְ���");
				break;
			case Imago::IT_MALE:
				m_TypeLabel->setString("������");
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
			auto ant = GameManager::getInstance()->getAnt();

			//action�� �ߴ��� ���̰� ���� ���
			if (ant->isDead())
			{
				addUpmoveLabel(2, "���̰� �׾���ȴ�!", 60);
				
				GameManager::getInstance()->initAnt();
				GameManager::getInstance()->antDie();

				m_AntSprite->removeFromParent();
				m_AntSprite = GameManager::getInstance()->getAnt()->getSprite();
				m_AntSprite->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2);
				addChild(m_AntSprite);

				setActButtonEnable(m_FeedItem, false);
				setActButtonEnable(m_BrainWashItem, false);
				setActButtonEnable(m_TrainItem, false);
				setActButtonEnable(m_InfiltrateItem, false);

				m_IsTrainVisible = false;

				m_TrainMenu->setVisible(m_IsTrainVisible);

				startAction(Egg::getEvolveTime(), nullptr);
			}
		}
	}

	m_StatWindow->update(dTime);
	m_EggNum->setString(std::to_string(GameManager::getInstance()->getAntNum()));
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

	setOriginalAni();

	addUpmoveLabel(1, "���ִ� ��!", 60);
}

void FosterScene::brainwashComplete()
{
	GameManager::getInstance()->getAnt()->addInt(1 + (rand() % 4));
	GameManager::getInstance()->getAnt()->addSatiety(-5 - (rand() % 5));
	GameManager::getInstance()->getAnt()->addAge(1 + (rand() % 3));

	setOriginalAni();

	addUpmoveLabel(1, "���̸� ������!", 60);
}

void FosterScene::battleCallback(cocos2d::Ref* sender)
{
	if (!m_IsAct)
	{
		setTrainAni();
		addUpmoveLabel(1, "���� ����!", 60);
		startAction(2.0f, std::bind(&FosterScene::battleComplete, this));
	}
}

void FosterScene::athleticCallback(cocos2d::Ref* sender)
{
	if (!m_IsAct)
	{
		setTrainAni();
		addUpmoveLabel(1, "ü���� ����!", 60);
		startAction(2.0f, std::bind(&FosterScene::athleticComplete, this));
	}
}

void FosterScene::exploreCallback(cocos2d::Ref* sender)
{
	if (!m_IsAct)
	{
		setTrainAni();
		addUpmoveLabel(1, "���� Ž������!", 60);
		startAction(2.0f, std::bind(&FosterScene::exploreComplete, this));
	}
}

void FosterScene::dodgeCallback(cocos2d::Ref* sender)
{
	if (!m_IsAct)
	{
		setTrainAni();
		addUpmoveLabel(1, "�Ϻ� ������ ���� �̺� ����!", 60);
		startAction(2.0f, std::bind(&FosterScene::dodgeComplete, this));
	}
}

void FosterScene::hellCallback(cocos2d::Ref* sender)
{
	if (!m_IsAct)
	{
		setTrainAni();
		addUpmoveLabel(1, "���ƾƾƾƾ�!", 60);
		startAction(2.0f, std::bind(&FosterScene::hellComplete, this));
	}
}

void FosterScene::battleComplete()
{
	GameManager::getInstance()->getAnt()->addStr(5 + (rand() % 10));
	GameManager::getInstance()->getAnt()->addSatiety(-7 - (rand() % 10));
	GameManager::getInstance()->getAnt()->addAge(3 + (rand() % 5));

	setOriginalAni();

	addUpmoveLabel(1, "���ݷ� ���!", 60);
}

void FosterScene::athleticComplete()
{
	GameManager::getInstance()->getAnt()->addHp(15 + (rand() % 20));
	GameManager::getInstance()->getAnt()->addSatiety(-10 - (rand() % 15));
	GameManager::getInstance()->getAnt()->addAge(4 + (rand() % 6));

	setOriginalAni();

	addUpmoveLabel(1, "ü�� ���!", 60);
}

void FosterScene::exploreComplete()
{
	//TODO : Ư�� �ɷ� ���� ���� �ֱ�
	setOriginalAni();
}

void FosterScene::dodgeComplete()
{
	//TODO : Ư�� �ɷ� ���� ���� �ֱ�
	setOriginalAni();

}

void FosterScene::hellComplete()
{
	int randomVal = rand() % 100;

	GameManager::getInstance()->getAnt()->addSatiety(-15 - (rand() % 10));
	GameManager::getInstance()->getAnt()->addAge(5 + (rand() % 20));

	//10% Ȯ���� ���
	if (randomVal < 10)
	{
		//�������� ������ 0���� �۰� ����� �����Ŵ
		GameManager::getInstance()->getAnt()->addSatiety(
			-GameManager::getInstance()->getAnt()->getSatiety() - 1);
	}
	else if (randomVal < 30) //20% Ȯ���� ���� 50%�� ����
	{
		GameManager::getInstance()->getAnt()->addHp(
			-GameManager::getInstance()->getAnt()->getHp() / 2);
		GameManager::getInstance()->getAnt()->addStr(
			-GameManager::getInstance()->getAnt()->getStr() / 2);
		GameManager::getInstance()->getAnt()->addInt(
			-GameManager::getInstance()->getAnt()->getInt() / 2);

		addUpmoveLabel(1, "�Ʒ� ����...", 60);
	}
	else // 70% Ȯ���� ���� ���� ���
	{
		GameManager::getInstance()->getAnt()->addHp(100 + (rand() % 50));
		GameManager::getInstance()->getAnt()->addStr(20 + (rand() % 20));
		GameManager::getInstance()->getAnt()->addInt(20 + (rand() % 20));

		addUpmoveLabel(1, "�뼺��! ���� �Ʒ� ������!", 60);
	}

	setOriginalAni();

}

void FosterScene::addUpmoveLabel(float duration, const std::string& text, float height)
{
	auto label = Label::createWithSystemFont(text, TEXT_FONT, 16);
	label->setColor(Color3B(0, 0, 0));
	addChild(label);
	auto move = MoveBy::create(duration, Point(0, height));
	auto fade = FadeOut::create(duration);
	auto spawn = Spawn::create(move, fade, nullptr);
	auto del = CallFunc::create(CC_CALLBACK_0(Label::removeFromParent, label));
	auto sequence = Sequence::create(spawn, del, nullptr);

	label->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME / 2 + 64);
	label->runAction(sequence);
}

void FosterScene::setTrainAni()
{
	auto imago = static_cast<Imago*>(GameManager::getInstance()->getAnt());

	switch (imago->getImagoType())
	{
	case Imago::IT_WORKER:
		runAnimation(m_AntSprite, GameManager::createAnimation("worker_train_%d.png", 1, 3, 0.2f));
		break;
	case Imago::IT_SOLDIER:
		break;
	}
}

void FosterScene::runAnimation(cocos2d::Sprite* sprite, cocos2d::Animation* animation)
{
	auto animate = Animate::create(animation);
	auto repeat = RepeatForever::create(animate);
	sprite->stopAllActions();
	sprite->runAction(repeat);
}

void FosterScene::setOriginalAni()
{
	auto ant = GameManager::getInstance()->getAnt();
	auto type = ant->getType();

	switch (type)
	{
	case Ant::ST_LARVA:
		runAnimation(m_AntSprite, GameManager::createAnimation("larva_%d.png", 1, 2, 0.3f));
		break;
	case Ant::ST_IMAGO:
		switch (static_cast<Imago*>(ant)->getImagoType())
		{
		case Imago::IT_WORKER:
			runAnimation(m_AntSprite, GameManager::createAnimation("worker_%d.png", 1, 4, 0.3f));
			break;
		case Imago::IT_SOLDIER:
			runAnimation(m_AntSprite, GameManager::createAnimation("soldier_%d.png", 1, 4, 0.3f));
			break;
		}
	}
}
