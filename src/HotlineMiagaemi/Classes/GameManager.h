#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"

class Ant;

class GameManager
{
public:
	static GameManager* getInstance();
	void releaseInstance();
	Ant* getAnt();
	void setAnt(Ant* ant);
	void initAnt();

private:
	GameManager();
	~GameManager();
	Ant* m_NowAnt;

	static GameManager* m_Instance;
};


#endif //_GAME_MANAGER_H_