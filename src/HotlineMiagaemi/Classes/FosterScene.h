//À°¼ºÇÏ´Â ¾À

#ifndef __FOSTER_SCENE_H__
#define __FOSTER_SCENE_H__

#include "cocos2d.h"

class FosterScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(FosterScene);
};

#endif // __FOSTER_SCENE_H__
