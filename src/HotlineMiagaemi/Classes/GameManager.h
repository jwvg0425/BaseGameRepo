#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"

class State;

class GameManager
{
public:
	static GameManager* getInstance();
	void releaseInstance();
	State* getAnt();
	void setAnt(State* ant);
	void initAnt();

private:
	GameManager();
	~GameManager();
	State* m_NowAnt;

	static GameManager* m_Instance;
};


#endif //_GAME_MANAGER_H_