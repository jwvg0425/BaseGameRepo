#ifndef __HALL_SCENE_H__
#define __HALL_SCENE_H__

#include "cocos2d.h"

class HallScene : public cocos2d::Layer
{
public:
    HallScene();
    virtual ~HallScene();

    static cocos2d::Scene* createScene();

    virtual bool init();
};
#endif
