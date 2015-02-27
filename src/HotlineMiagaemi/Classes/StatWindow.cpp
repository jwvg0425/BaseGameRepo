#include "StatWindow.h"
#include "const.h"
#include "GameManager.h"

const std::string HP_LABEL = "체력 : ";
const std::string INT_LABEL = "지능 : ";
const std::string STR_LABEL = "공격력 : ";
const std::string AGE_LABEL = "나이 : ";
const std::string SAT_LABEL = "포만감 : ";

USING_NS_CC;

StatWindow::StatWindow() :
m_Window(nullptr), m_Hp(nullptr), m_Int(nullptr), m_Str(nullptr), m_Sat(nullptr), m_Life(nullptr),
m_PrevHp(0), m_PrevInt(0), m_PrevStr(0), m_PrevSat(0), m_PrevAge(-1)
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

	initLabel();

	return true;
}

void StatWindow::update(float dTime)
{
	updateLabel();
}

void StatWindow::initLabel()
{
	m_Hp = Label::createWithSystemFont(HP_LABEL, TEXT_FONT, 16);
	m_Hp->setAnchorPoint(Point(0, 0));
	m_Hp->setPosition(-60, 80);
	m_Hp->setColor(Color3B(0, 0, 0));
	m_Str = Label::createWithSystemFont(STR_LABEL, TEXT_FONT, 16);
	m_Str->setAnchorPoint(Point(0, 0));
	m_Str->setPosition(-60, 40);
	m_Str->setColor(Color3B(0, 0, 0));
	m_Int = Label::createWithSystemFont(INT_LABEL, TEXT_FONT, 16);
	m_Int->setAnchorPoint(Point(0, 0));
	m_Int->setPosition(-60, 0);
	m_Int->setColor(Color3B(0, 0, 0));
	m_Sat = Label::createWithSystemFont(SAT_LABEL, TEXT_FONT, 16);
	m_Sat->setAnchorPoint(Point(0, 0));
	m_Sat->setPosition(-60, -40);
	m_Sat->setColor(Color3B(0, 0, 0));
	m_Life = Label::createWithSystemFont(AGE_LABEL, TEXT_FONT, 16);
	m_Life->setAnchorPoint(Point(0, 0));
	m_Life->setPosition(-60, -80);
	m_Life->setColor(Color3B(0, 0, 0));

	addChild(m_Hp);
	addChild(m_Str);
	addChild(m_Int);
	addChild(m_Sat);
	addChild(m_Life);
}

void StatWindow::updateLabel()
{
	auto ant = GameManager::getInstance()->getAnt();

	int hpValue = ant->getHp();
	int strValue = ant->getStr();
	int intValue = ant->getInt();
	int satValue = ant->getSatiety();
	int ageValue = ant->getAge();

	switch (ant->getType())
	{
	case Ant::ST_EGG:
		intValue = -1;
		satValue = -1;
	case Ant::ST_LARVA:
		hpValue = -1;
		strValue = -1;
	case Ant::ST_IMAGO:
		break;
	}

	if (hpValue != m_PrevHp)
	{
		m_Hp->setString(HP_LABEL + (hpValue == -1 ? std::string("??") : std::to_string(hpValue)));
		m_PrevHp = hpValue;
	}

	if (strValue != m_PrevStr)
	{
		m_Str->setString(STR_LABEL + (strValue == -1 ? std::string("??") : std::to_string(strValue)));
		m_PrevStr = strValue;
	}

	if (intValue != m_PrevInt)
	{
		m_Int->setString(INT_LABEL + (intValue == -1 ? std::string("??") : std::to_string(intValue)));
		m_PrevInt = intValue;
	}

	if (satValue != m_PrevSat)
	{
		m_Sat->setString(SAT_LABEL + (satValue == -1 ? std::string("??") : std::to_string(satValue)));
		m_PrevSat = satValue;
	}

	if (ageValue != m_PrevAge)
	{
		m_Life->setString(AGE_LABEL + (ageValue == -1 ? std::string("??") : std::to_string(ageValue)));
		m_PrevAge = ageValue;
	}
}
