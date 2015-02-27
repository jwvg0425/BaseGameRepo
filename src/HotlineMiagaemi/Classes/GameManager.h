#include "cocos2d.h"

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

class Ant;

class GameManager
{
public:
	static GameManager* getInstance();
	void releaseInstance();
	Ant* getAnt();

private:
	GameManager();
	~GameManager();
	Ant* m_NowAnt;

	static GameManager* m_Instance;
};


#endif //_GAME_MANAGER_H_