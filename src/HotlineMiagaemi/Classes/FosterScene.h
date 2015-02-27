//À°¼ºÇÏ´Â ¾À

#ifndef __FOSTER_SCENE_H__
#define __FOSTER_SCENE_H__

#include "cocos2d.h"

class FosterScene : public cocos2d::LayerColor
{
public:
	FosterScene();
	~FosterScene();

    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(FosterScene);

private:
	cocos2d::MenuItem* createActButton(const std::string& labelText);

	cocos2d::Menu* m_ActMenu;
};

#endif // __FOSTER_SCENE_H__
