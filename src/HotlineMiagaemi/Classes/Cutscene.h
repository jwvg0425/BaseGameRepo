//½ºÅä¸® ÄÆ ¾À

#ifndef __CUT_SCENE_H__
#define __CUT_SCENE_H__

#include "cocos2d.h"

class CutScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(CutScene);
};

#endif // __CUT_SCENE_H__

