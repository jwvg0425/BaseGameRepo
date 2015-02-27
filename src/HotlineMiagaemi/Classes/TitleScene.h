
#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	void endAnimation(cocos2d::Ref* sender);

	CREATE_FUNC(TitleScene);

private:
	bool m_Enable;
};


#endif //_TITLE_SCENE_H_