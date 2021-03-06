﻿#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"
#include "Ant.h"
#include "const.h"

class Imago;
class GameManager
{
public:
	static GameManager* getInstance();
	void releaseInstance();
	Ant* getAnt();
    Imago* getQueen();
	void setAnt(Ant* ant);
	void antDie();
	int getAntNum();
	void initAnt();
    void initQueen();
	void initSubtileNames();
	void initSprites();
	cocos2d::Animation* getAnimation(Ant* ant);
	static cocos2d::Animation* createAnimation
		(const char* format, int startIdx, size_t frameNum, float delay);

	static void runAnimation(cocos2d::Sprite* sprite, cocos2d::Animation* animation);

	cocos2d::Sprite* getSubtile(Direction parts, int surrounds);

private:
	
	GameManager();
	~GameManager();
	Ant* m_NowAnt;
    Imago* m_QueenAnt;
	int m_AntNum;
	std::map<Direction, std::map<int, std::string>> m_SubtileNames;

	static GameManager* m_Instance;
};


#endif //_GAME_MANAGER_H_