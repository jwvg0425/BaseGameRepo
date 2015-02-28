
#ifndef _HALL_SPRITE_H_
#define _HALL_SPRITE_H_

#include "cocos2d.h"

class Imago;
class HallSprite : public cocos2d::Node
{
public:
	HallSprite();
	~HallSprite();

	virtual bool init();

	void update(float dTime);

	CREATE_FUNC(HallSprite);

private:
	cocos2d::Sprite* m_PlayerSprite;
	cocos2d::Sprite* m_CursorSprite;
	int m_PrevYPos;
	int m_PrevXPos;
	int m_Camera;

	//anchorPoint 0.5,0.5 기준
	void addTile(float x, float y, 
		const std::string& upright, const std::string& rightdown, const std::string& downleft, const std::string& leftup);

	std::map<Imago*, cocos2d::Point> m_PrevEnemyPos;
	std::map<Imago*, cocos2d::Sprite*> m_EnemySprites;
};


#endif //_HALL_SPRITE_H_