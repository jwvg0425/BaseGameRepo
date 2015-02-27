
#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	void endAnimation(cocos2d::Ref* sender);
	void sceneChange(cocos2d::Ref* sender);

	CREATE_FUNC(TitleScene);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

private:
	bool m_Enable;
	int m_Num;
	cocos2d::Sprite* m_Image;
};


#endif //_TITLE_SCENE_H_