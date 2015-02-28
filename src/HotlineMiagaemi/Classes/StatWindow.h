
#ifndef _STAT_WINDOW_H_
#define _STAT_WINDOW_H_

#include "cocos2d.h"

class StatWindow : public cocos2d::Node
{
public:
	StatWindow();
	~StatWindow();

	virtual bool init();

	void update(float dTime);
	void setOpacity(GLubyte opacity);

	CREATE_FUNC(StatWindow);

private:
	void initLabel();
	void updateStat();
	void updateLabel();

	cocos2d::Sprite* m_Window;
	cocos2d::Label* m_Hp; //체력
	cocos2d::Label* m_Int; //지능
	cocos2d::Label* m_Str; //공격력
	cocos2d::Label* m_Sat; //포만감
	cocos2d::Label* m_Life; //나이

	int m_PrevHp;
	int m_PrevInt;
	int m_PrevStr;
	int m_PrevSat;
	int m_PrevAge;
};

#endif //_STAT_WINDOW_H_