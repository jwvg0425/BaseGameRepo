#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"
#include "Ant.h"

class GameManager
{
public:
	static GameManager* getInstance();
	void releaseInstance();
	Ant* getAnt();
	void setAnt(Ant* ant);
	void initAnt();
	cocos2d::Animation* getAnimation(Ant* ant);

private:
	GameManager();
	~GameManager();
	Ant* m_NowAnt;

	cocos2d::Animation* createAnimation(const char* format, int startIdx, size_t frameNum, float delay);

	static GameManager* m_Instance;
};


#endif //_GAME_MANAGER_H_