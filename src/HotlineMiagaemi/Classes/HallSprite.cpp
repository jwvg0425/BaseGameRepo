#include "HallSprite.h"
#include "const.h"
#include "TunnelManager.h"
#include "HallScene.h"

USING_NS_CC;

HallSprite::HallSprite() : m_PlayerSprite(nullptr)
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

	for (int y = 0; y > -200; y--)
	{
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
		if (manager->isRoomExist(-1, y))
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_09.png", "tile/subtile_09.png");
		}
		else if (manager->isRoomExist(-1, y + 1))
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_09.png", "tile/subtile_09.png");
		}
		else if (manager->isRoomExist(-1, y - 1))
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_00.png", "tile/subtile_00.png", "tile/subtile_09.png", "tile/subtile_09.png");
		}
		else
		{
			addTile(WND_WIDTH_GAME / 2 - 64 * 2, WND_HEIGHT_GAME - 32 + (y + 1) * 64,
				"tile/subtile_01.png", "tile/subtile_01.png", "tile/subtile_09.png", "tile/subtile_09.png");
		}

		if (manager->isRoomExist(1, y))
		{
		}
		else
		{
		}
	}

	m_PrevYPos = 0;
	
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


	if (yPos != m_PrevYPos)
	{
		runAction(MoveBy::create(0.5, Point(0, 64)));
		m_PrevYPos = yPos;
	}
}
