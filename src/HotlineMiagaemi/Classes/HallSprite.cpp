#include "HallSprite.h"
#include "const.h"
#include "TunnelManager.h"
#include "HallScene.h"
#include "GameManager.h"

USING_NS_CC;

HallSprite::HallSprite() : m_PlayerSprite(nullptr), m_Camera(0)
{

}

HallSprite::~HallSprite()
{

}

bool HallSprite::init()
{
	if (!Node::init())
	{
		return false;
	}

	for (int y = 0; y >= -200; y--)
	{
		auto game = GameManager::getInstance();
		auto manager = TunnelManager::getInstance();

		//중앙 3칸 복도
		addTile(WND_WIDTH_GAME / 2 - 64, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png");
		addTile(WND_WIDTH_GAME / 2 + 64, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png");
		addTile(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_00.png");

		//좌우 끝 벽(무조건)
		addTile(WND_WIDTH_GAME / 2 - 64 * 3, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png");
		addTile(WND_WIDTH_GAME / 2 + 64 * 3, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png");
		addTile(WND_WIDTH_GAME / 2 - 64 * 4, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png");
		addTile(WND_WIDTH_GAME / 2 + 64 * 4, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
			"tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_01.png");

		//방 존재 여부에 따라 달라지는 부분
		if (manager->isRoomExist(-1, y + 1))
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_09.png", "tile/subtile_09.png");
		}
		else if (manager->isRoomExist(-1, y + 2))
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_03.png", "tile/subtile_09.png", "tile/subtile_01.png", "tile/subtile_11.png");
		}
		else if (manager->isRoomExist(-1, y))
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_05.png", "tile/subtile_00.png", "tile/subtile_09.png", "tile/subtile_06.png");
		}
		else
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_09.png", "tile/subtile_09.png", "tile/subtile_01.png", "tile/subtile_01.png");
		}

		if (manager->isRoomExist(1, y + 1))
		{
			addTile(WND_WIDTH_GAME / 2 + 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_10.png", "tile/subtile_10.png", "tile/subtile_00.png", "tile/subtile_00.png");
		}
		else if (manager->isRoomExist(1, y + 2))
		{
			addTile(WND_WIDTH_GAME / 2 + 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_13.png", "tile/subtile_01.png", "tile/subtile_10.png", "tile/subtile_02.png");
		}
		else if (manager->isRoomExist(1, y))
		{
			addTile(WND_WIDTH_GAME / 2 + 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_01.png", "tile/subtile_08.png", "tile/subtile_04.png", "tile/subtile_10.png");
		}
		else
		{
			addTile(WND_WIDTH_GAME / 2 + 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_10.png", "tile/subtile_10.png");
		}
	}

	m_PrevXPos = 0;
	m_PrevYPos = 0;

	auto ant = GameManager::getInstance()->getAnt();
	m_PlayerSprite = ant->getSprite();
	m_PlayerSprite->setFlippedY(true);
	auto animation = GameManager::getInstance()->getAnimation(ant);

	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);
		m_PlayerSprite->runAction(repeat);
	}

	addChild(m_PlayerSprite);

	m_PlayerSprite->setPosition(WND_WIDTH_GAME / 2, WND_HEIGHT_GAME - 32);
	
	scheduleUpdate();

	return true;
}

void HallSprite::addTile(float x, float y,
	const std::string& upright, const std::string& rightdown, const std::string& downleft, const std::string& leftup)
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

void HallSprite::update(float dTime)
{
	int yPos = static_cast<HallScene*>(getParent())->getAntYPos();
	int xPos = static_cast<HallScene*>(getParent())->getAntXPos();

	if (yPos != m_PrevYPos)
	{
		if (yPos > m_PrevYPos)
		{
			if (m_Camera > 0)
			{
				runAction(MoveBy::create(0.5, Point(0, -64)));
				m_Camera--;
			}
			m_PlayerSprite->setRotation(180);
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(0, 64)));
			
		}
		else
		{
			if (yPos < -4)
			{
				runAction(MoveBy::create(0.5, Point(0, 64)));
				m_Camera++;
			}
			m_PlayerSprite->setRotation(0);
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(0, -64)));
			
		}
		m_PrevYPos = yPos;
	}

	if (xPos != m_PrevXPos)
	{
		if (xPos > m_PrevXPos)
		{
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(64, 0)));
			m_PlayerSprite->setRotation(270);
		}
		else
		{
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(-64, 0)));
			m_PlayerSprite->setRotation(90);
		}
		m_PrevXPos = xPos;
	}
}
