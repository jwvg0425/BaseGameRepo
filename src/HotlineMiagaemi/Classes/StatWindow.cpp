#include "StatWindow.h"

USING_NS_CC;

StatWindow::StatWindow() :
m_Window(nullptr), m_Hp(nullptr), m_Int(nullptr), m_Str(nullptr), m_Sat(nullptr),
m_PrevHp(0), m_PrevInt(0), m_PrevStr(0), m_PrevSat(0)
{

}

StatWindow::~StatWindow()
{

}

bool StatWindow::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_Window = Sprite::create("stat_window.png");

	addChild(m_Window);
	m_Window->setPosition(0, 0);
	m_Window->setAnchorPoint(Point(0.5, 0.5));

	return true;
}

void StatWindow::update(float dTime)
{

}
