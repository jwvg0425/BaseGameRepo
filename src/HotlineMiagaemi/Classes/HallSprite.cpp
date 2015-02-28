#include "HallSprite.h"
#include "const.h"
#include "TunnelManager.h"
#include "HallScene.h"
#include "GameManager.h"
#include "Imago.h"

USING_NS_CC;

HallSprite::HallSprite() : m_PlayerSprite(nullptr), m_CursorSprite(nullptr), m_Camera(0)
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

	//몬스터 위치 초기화

	auto antList = TunnelManager::getInstance()->getHallAntList();

	for (int i = 0; i < antList.size(); i++)
	{
		int x = antList[i]->getPosX();
		int y = antList[i]->getPosY();
		m_PrevEnemyPos[antList[i]] = Point(x, y);
		m_EnemySprites[antList[i]] = antList[i]->getSprite();

		addChild(m_EnemySprites[antList[i]]);

		m_EnemySprites[antList[i]]->setAnchorPoint(Point(0.5, 0.5));
		m_EnemySprites[antList[i]]->setPosition(WND_WIDTH_GAME / 2 + x * 64, WND_HEIGHT_GAME - 32 + y * 64);

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
			//TODO : princess 그래픽 만들어주면 추가하기
		case Imago::IT_PRINCESS:
			break;
		}

		GameManager::runAnimation(m_EnemySprites[antList[i]], animation);
	}

	m_PrevXPos = 0;
	m_PrevYPos = 0;

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

	GameManager::runAnimation(m_CursorSprite,GameManager::createAnimation("cursor_%d.png", 1, 4, 0.3f));

	m_CursorSprite->setAnchorPoint(Point(0.5, 0.5));
	m_CursorSprite->setOpacity(128);

	addChild(m_CursorSprite);
	
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
			if (m_Camera > 0)
			{
				runAction(MoveBy::create(0.5, Point(0, -64)));
				m_Camera--;
			}
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(0, 64)));
		}
		else
		{
			if (yPos < -4)
			{
				runAction(MoveBy::create(0.5, Point(0, 64)));
				m_Camera++;
			}
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(0, -64)));
			
		}
		m_PrevYPos = yPos;
	}

	if (xPos != m_PrevXPos)
	{
		if (xPos > m_PrevXPos)
		{
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(64, 0)));
		}
		else
		{
			m_PlayerSprite->runAction(MoveBy::create(0.5, Point(-64, 0)));
		}
		m_PrevXPos = xPos;
	}

	m_CursorSprite->setPosition(m_PlayerSprite->getPositionX(), m_PlayerSprite->getPositionY() + 32);

	auto antList = TunnelManager::getInstance()->getHallAntList();

	for (int i = 0; i < antList.size(); i++)
	{
		int xPos = antList[i]->getPosX();
		int yPos = antList[i]->getPosY();
		int prevXPos = m_PrevEnemyPos[antList[i]].x;
		int prevYPos = m_PrevEnemyPos[antList[i]].y;

		if (xPos != prevXPos || yPos != prevYPos)
		{
			m_EnemySprites[antList[i]]->runAction(MoveTo::create(0.5, 
				Point(WND_WIDTH_GAME / 2 +xPos*64, WND_HEIGHT_GAME - 32 + yPos * 64)));

			m_PrevEnemyPos[antList[i]].x = xPos;
			m_PrevEnemyPos[antList[i]].y = yPos;
		}

		//방향 변경

		switch (antList[i]->getDir())
		{
		case DIR_LEFT:
			m_EnemySprites[antList[i]]->setRotation(270);
			break;
		case DIR_UP:
			m_EnemySprites[antList[i]]->setRotation(0);
			break;
		case DIR_RIGHT:
			m_EnemySprites[antList[i]]->setRotation(90);
			break;
		case DIR_DOWN:
			m_EnemySprites[antList[i]]->setRotation(180);
			break;
		}
	}

	for (auto& sprites : m_EnemySprites)
	{
		//해당 스프라이트가 존재하는 스프라이트인지 검사
		if (![&]() -> bool
		{
			for (int i = 0; i < antList.size(); i++)
			{
				if (antList[i] == sprites.first)
				{
					return true;
				}
			}

			return false;
		}())
		{
			sprites.second->removeFromParent();
		}
	}
}
