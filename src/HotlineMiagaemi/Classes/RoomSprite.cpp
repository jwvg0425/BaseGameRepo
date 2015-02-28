#include "RoomSprite.h"
#include "Imago.h"
#include "RoomScene.h"
#include "GameManager.h"

USING_NS_CC;

RoomSprite::RoomSprite()
{

}

RoomSprite::~RoomSprite()
{

}

bool RoomSprite::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_PrevXPos = 0;
	m_PrevYPos = 0;

	return true;
}

void RoomSprite::update(float dTime)
{
	//플레이어 이동
	int yPos = m_Room->getAntYPos();
	int xPos = m_Room->getAntXPos();

	switch (GameManager::getInstance()->getAnt()->getDir())
	{
	case DIR_LEFT:
		m_PlayerSprite->setRotation(270);
		break;
	case DIR_UP:
		m_PlayerSprite->setRotation(0);
		break;
	case DIR_RIGHT:
		m_PlayerSprite->setRotation(90);
		break;
	case DIR_DOWN:
		m_PlayerSprite->setRotation(180);
		break;
	}

	if (yPos != m_PrevYPos)
	{
		if (yPos > m_PrevYPos)
		{
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(0, 64)));
		}
		else
		{
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(0, -64)));

		}
		m_PrevYPos = yPos;
	}

	if (xPos != m_PrevXPos)
	{
		m_PrevXPos = xPos;
	}

	m_CursorSprite->setPosition(m_PlayerSprite->getPositionX(), m_PlayerSprite->getPositionY() + 32);

}

void RoomSprite::addTile(float x, float y, const std::string& upright, const std::string& rightdown, const std::string& downleft, const std::string& leftup)
{
	auto subUpright = Sprite::create(upright);
	auto subRightdown = Sprite::create(rightdown);
	auto subDownleft = Sprite::create(downleft);
	auto subLeftup = Sprite::create(leftup);

	subUpright->setAnchorPoint(Point(0, 0));
	subUpright->setPosition(x, y);
	subRightdown->setAnchorPoint(Point(0, 0));
	subRightdown->setPosition(x, y - 32);
	subDownleft->setAnchorPoint(Point(0, 0));
	subDownleft->setPosition(x - 32, y - 32);
	subLeftup->setAnchorPoint(Point(0, 0));
	subLeftup->setPosition(x - 32, y);

	addChild(subUpright);
	addChild(subRightdown);
	addChild(subDownleft);
	addChild(subLeftup);
}

bool RoomSprite::initWithScene(RoomScene* scene)
{
	m_Room = scene;

	int sizeX = m_Room->getRoomSizeX();
	int sizeY = m_Room->getRoomsizeY();

	//기본 배경 타일 추가
	for (int y = 0; y >= sizeY; y--)
	{
		int startX = 0;
		if (m_Room->isLeft())
		{
			startX -= sizeX;
		}

		for (int x = startX; x <= startX + sizeX; x++)
		{
			addTile(x * 64, (y + 1) * 64,
				"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png");
		}
	}

	//몬스터 추가

	auto antList = m_Room->getRoomAntList();

	for (int i = 0; i < antList.size(); i++)
	{
		int x = antList[i]->getPosX();
		int y = antList[i]->getPosY();
		m_PrevEnemyPos[antList[i]] = Point(x, y);
		m_EnemySprites[antList[i]] = antList[i]->getSprite();

		addChild(m_EnemySprites[antList[i]]);

		m_EnemySprites[antList[i]]->setAnchorPoint(Point(0.5, 0.5));
		m_EnemySprites[antList[i]]->setPosition(x * 64, y * 64);

		cocos2d::Animation* animation = nullptr;

		switch (antList[i]->getImagoType())
		{
		case Imago::IT_WORKER:
			animation = GameManager::createAnimation("worker_%d.png", 1, 4, 0.3f);
			break;
		case Imago::IT_SOLDIER:
			animation = GameManager::createAnimation("soldier_%d.png", 1, 4, 0.3f);
			break;
		case Imago::IT_MALE:
			animation = GameManager::createAnimation("male_%d.png", 1, 4, 0.3f);
			break;
		}

		GameManager::runAnimation(m_EnemySprites[antList[i]], animation);
	}

	auto ant = GameManager::getInstance()->getAnt();
	m_PlayerSprite = ant->getSprite();
	auto animation = GameManager::getInstance()->getAnimation(ant);

	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);
		m_PlayerSprite->runAction(repeat);
	}

	addChild(m_PlayerSprite);

	m_PlayerSprite->setPosition(0, 0);
	GameManager::getInstance()->getAnt()->setDir(DIR_DOWN);

	m_CursorSprite = Sprite::create("cursor_1.png");

	GameManager::runAnimation(m_CursorSprite, GameManager::createAnimation("cursor_%d.png", 1, 4, 0.3f));

	m_CursorSprite->setAnchorPoint(Point(0.5, 0.5));
	m_CursorSprite->setOpacity(128);

	addChild(m_CursorSprite);

	scheduleUpdate();

	return true;
}
