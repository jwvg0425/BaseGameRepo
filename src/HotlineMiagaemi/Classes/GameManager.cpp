#include "GameManager.h"
#include "Egg.h"

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

GameManager::GameManager() : m_NowAnt(nullptr)
{
	initAnt();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("larva.plist");
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
	m_NowAnt = new Egg();
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
