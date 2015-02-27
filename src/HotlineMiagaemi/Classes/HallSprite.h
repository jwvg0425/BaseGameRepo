
#ifndef _HALL_SPRITE_H_
#define _HALL_SPRITE_H_

#include "cocos2d.h"

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
	int m_PrevYPos;

	//anchorPoint 0.5,0.5 기준
	void addTile(float x, float y, 
		const std::string& upright, const std::string& rightdown, const std::string& downleft, const std::string& leftup);
};


#endif //_HALL_SPRITE_H_