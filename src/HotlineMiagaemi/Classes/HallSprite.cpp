#include "HallSprite.h"

USING_NS_CC;

HallSprite::HallSprite() :
m_Background(nullptr), m_PlayerSprite(nullptr)
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
	}

	return true;
}