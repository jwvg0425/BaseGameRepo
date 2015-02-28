#include "GameManager.h"
#include "Egg.h"
#include "Imago.h"
#include "const.h"

GameManager* GameManager::m_Instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager;
	}

	return m_Instance;
}

void GameManager::releaseInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

GameManager::GameManager() : m_NowAnt(nullptr), m_AntNum(5)
{
	initAnt();
	initSubtileNames();
	initSprites();
}

GameManager::~GameManager()
{

}

Ant* GameManager::getAnt()
{
	return m_NowAnt;
}

void GameManager::initAnt()
{
	setAnt(new Egg());
}

void GameManager::setAnt(Ant* ant)
{
	if (m_NowAnt != nullptr)
	{
		delete m_NowAnt;
	}

	m_NowAnt = ant;
}

cocos2d::Animation* GameManager::getAnimation(Ant* ant)
{
	auto type = ant->getType();

	switch (type)
	{
	case Ant::ST_NONE:
		return nullptr;
	case Ant::ST_EGG:
		return nullptr;
	case Ant::ST_LARVA:
		return createAnimation("larva_%d.png", 1, 2, 0.3f);
	case Ant::ST_IMAGO:
		switch (static_cast<Imago*>(ant)->getImagoType())
		{
		case Imago::IT_WORKER:
			return createAnimation("worker_%d.png", 1, 4, 0.3f);
		case Imago::IT_SOLDIER:
			return createAnimation("soldier_%d.png", 1, 4, 0.3f);
		case Imago::IT_MALE:
			return createAnimation("male_%d.png", 1, 4, 0.3f);
		}
		return nullptr;
	}

	return nullptr;
}

cocos2d::Animation* GameManager::createAnimation(const char* format, int startIdx, size_t frameNum, float delay)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(delay);

	for (size_t i = 0; i < frameNum; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format(format, i + startIdx));
		animation->addSpriteFrame(frame);
	}
	
	animation->retain();
	return animation;
}

int GameManager::getAntNum()
{
	return m_AntNum;
}

cocos2d::Sprite* GameManager::getSubtile(Direction parts, int surrounds)
{
	return Sprite::create(m_SubtileNames[parts][surrounds]);
}

void GameManager::initSubtileNames()
{
	m_SubtileNames[DIR_RIGHTDOWN][DIR_RIGHT | DIR_RIGHTDOWN | DIR_DOWN] =
		m_SubtileNames[DIR_UPRIGHT][DIR_UP | DIR_UPRIGHT | DIR_RIGHT] =
		m_SubtileNames[DIR_LEFTUP][DIR_LEFT | DIR_LEFTUP | DIR_LEFT] =
		m_SubtileNames[DIR_DOWNLEFT][DIR_DOWN | DIR_DOWNLEFT | DIR_LEFT] =
		"tile/subtile_01.png";

	m_SubtileNames[DIR_LEFTUP][DIR_NONE] =
		m_SubtileNames[DIR_LEFTUP][DIR_LEFTUP] =
		"tile/subtile_02.png";

	m_SubtileNames[DIR_UPRIGHT][DIR_NONE] =
		m_SubtileNames[DIR_UPRIGHT][DIR_UPRIGHT] =
		"tile/subtile_03.png";

	m_SubtileNames[DIR_DOWNLEFT][DIR_NONE] =
		m_SubtileNames[DIR_DOWNLEFT][DIR_DOWNLEFT] =
		"tile/subtile_04.png";

	m_SubtileNames[DIR_RIGHTDOWN][DIR_NONE] =
		m_SubtileNames[DIR_RIGHTDOWN][DIR_RIGHTDOWN] =
		"tile/subtile_05.png";

	m_SubtileNames[DIR_RIGHTDOWN][DIR_RIGHT | DIR_DOWN] =
		"tile/subtile_06.png";

	m_SubtileNames[DIR_DOWNLEFT][DIR_DOWN | DIR_LEFT] =
		"tile/subtile_08.png";

	m_SubtileNames[DIR_LEFTUP][DIR_LEFT | DIR_UP] =
		"tile/subtile_13.png";

	m_SubtileNames[DIR_UPRIGHT][DIR_UP | DIR_RIGHT] =
		"tile/subtile_11.png";

	m_SubtileNames[DIR_DOWNLEFT][DIR_LEFT] =
		m_SubtileNames[DIR_DOWNLEFT][DIR_LEFT | DIR_DOWNLEFT] =
		m_SubtileNames[DIR_RIGHTDOWN][DIR_RIGHT] =
		m_SubtileNames[DIR_RIGHTDOWN][DIR_RIGHT | DIR_RIGHTDOWN] =
		"tile/subtile_07.png";

	m_SubtileNames[DIR_UPRIGHT][DIR_UP] =
		m_SubtileNames[DIR_UPRIGHT][DIR_UP | DIR_UPRIGHT] =
		m_SubtileNames[DIR_RIGHTDOWN][DIR_DOWN] =
		m_SubtileNames[DIR_RIGHTDOWN][DIR_DOWN | DIR_RIGHTDOWN] =
		"tile/subtile_09.png";

	m_SubtileNames[DIR_LEFTUP][DIR_UP] =
		m_SubtileNames[DIR_LEFTUP][DIR_UP | DIR_LEFTUP] =
		m_SubtileNames[DIR_DOWNLEFT][DIR_DOWN] =
		m_SubtileNames[DIR_DOWNLEFT][DIR_DOWN | DIR_DOWNLEFT] =
		"tile/subtile_10.png";

	m_SubtileNames[DIR_UPRIGHT][DIR_RIGHT] =
		m_SubtileNames[DIR_UPRIGHT][DIR_RIGHT | DIR_UPRIGHT] =
		m_SubtileNames[DIR_LEFTUP][DIR_LEFT] =
		m_SubtileNames[DIR_LEFTUP][DIR_LEFT | DIR_LEFTUP] =
		"tile/subtile_12.png";

}

void GameManager::antDie()
{
	m_AntNum--;

	if (m_AntNum < 0)
	{
		// TODO: 게임 오버 씬으로 넘어가게 지금은 그냥 게임 종료.
		Director::getInstance()->end();
	}
}

void GameManager::initSprites()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("larva.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("larva_brainwash.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("larva_feed.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("worker.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("worker_feed.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("worker_brainwash.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("worker_train.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldier.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldier_feed.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldier_brainwash.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldier_train.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("male.plist");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cursor.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect.plist");
}

void GameManager::runAnimation(cocos2d::Sprite* sprite, cocos2d::Animation* animation)
{
	auto animate = Animate::create(animation);
	auto repeat = RepeatForever::create(animate);
	sprite->stopAllActions();
	sprite->runAction(repeat);
}