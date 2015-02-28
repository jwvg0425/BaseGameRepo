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
	return true;
}

void RoomSprite::update(float dTime)
{

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
	for (int y = 0; y <= -sizeY; y++)
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

	m_PlayerSprite->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME - 32);
	GameManager::getInstance()->getAnt()->setDir(DIR_DOWN);

	m_CursorSprite = Sprite::create("cursor_1.png");

	GameManager::runAnimation(m_CursorSprite, GameManager::createAnimation("cursor_%d.png", 1, 4, 0.3f));

	m_CursorSprite->setAnchorPoint(Point(0.5, 0.5));
	m_CursorSprite->setOpacity(128);

	addChild(m_CursorSprite);

	scheduleUpdate();

	return true;
}
