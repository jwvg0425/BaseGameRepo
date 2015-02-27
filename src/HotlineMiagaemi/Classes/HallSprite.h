
#ifndef _HALL_SPRITE_H_
#define _HALL_SPRITE_H_

#include "cocos2d.h"

class HallSprite : public cocos2d::Node
{
public:
	HallSprite();
	~HallSprite();

	virtual bool init();

	CREATE_FUNC(HallSprite);

private:
	cocos2d::Sprite* m_Background;
	cocos2d::Sprite* m_PlayerSprite;
};


#endif //_HALL_SPRITE_H_