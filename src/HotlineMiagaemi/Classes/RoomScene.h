#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"

enum RoomType
{
    RT_NONE,
    RT_EGG,
    RT_PRINCESS,
    RT_QUEEN
};

class RoomScene : public cocos2d::Layer
{
public:
    RoomScene();
    ~RoomScene();

    static cocos2d::Scene* createScene(RoomType roomType);

    virtual bool init();

    void setRoomType(RoomType type){ m_RoomType = type; }

protected:
    RoomType         m_RoomType;
};

#endif

