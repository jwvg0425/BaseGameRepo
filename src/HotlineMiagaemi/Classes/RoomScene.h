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

    cocos2d::MenuItem* createActButton(const std::string& labelText, cocos2d::ccMenuCallback callback);

    void setActButtonEnable(cocos2d::MenuItem* item, bool enable);

    static cocos2d::Scene* createScene(RoomType roomType, bool isLeft, int sizeX, int sizeY);

    virtual bool init();

    CREATE_FUNC(RoomScene);

    void setRoomType(RoomType type){ m_RoomType = type; }
    void setRoomSizeX(int sizeX){ m_SizeX = sizeX; }
    void setRoomSizeY(int sizeY){ m_SizeY = sizeY; }
    void setIsLeft(bool isLeft){ m_IsLeft = isLeft; }

    void moveCallback(cocos2d::Ref* ref);

private:
    RoomType            m_RoomType;
    cocos2d::Menu*      m_ActMenu;
    cocos2d::MenuItem*  m_MoveItem;
    int                 m_AntXPos;
    int                 m_AntYPos;
    int                 m_SizeX;
    int                 m_SizeY;
    bool                m_IsLeft;
};

#endif

