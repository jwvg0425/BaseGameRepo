
#ifndef _ROOM_SPRITE_H_
#define _ROOM_SPRITE_H_

#include "cocos2d.h"

class Imago;
class RoomScene;
class RoomSprite : public cocos2d::Node
{
public:
	RoomSprite();
	~RoomSprite();

	virtual bool init();

	virtual bool initWithScene(RoomScene* scene);

	void update(float dTime);

	CREATE_FUNC(RoomSprite);
private:
	cocos2d::Sprite* m_PlayerSprite;
	cocos2d::Sprite* m_CursorSprite;

	//anchorPoint 0.5,0.5 기준
	void addTile(float x, float y,
		const std::string& upright, const std::string& rightdown, const std::string& downleft, const std::string& leftup);

	std::map<Imago*, cocos2d::Point> m_PrevEnemyPos;
	std::map<Imago*, cocos2d::Sprite*> m_EnemySprites;
	RoomScene* m_Room;
};

#endif //_ROOM_SPRITE_H_