#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"

class RoomSprite;
class Imago;
enum RoomType
{
    RT_NONE,
    RT_EGG,
    RT_MALE,
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
	void initSprite();

    CREATE_FUNC(RoomScene);

    void setRoomType(RoomType type){ m_RoomType = type; }
    void setRoomSizeX(int sizeX){ m_SizeX = sizeX; }
    void setRoomSizeY(int sizeY){ m_SizeY = sizeY; }
	void setIsLeft(bool isLeft);

    void moveCallback(cocos2d::Ref* ref);
    void outCallback(cocos2d::Ref* ref);

    RoomType getRoomType(){ return m_RoomType; }
    int getRoomSizeX(){ return m_SizeX; }
    int getRoomsizeY(){ return m_SizeY; }
    bool isLeft(){ return m_IsLeft; }

	int getAntXPos();
	int getAntYPos();
	const std::vector<Imago*>& getRoomAntList();

    bool checkRoomAnt(int x, int y);

private:
    RoomType            m_RoomType;
    std::vector<Imago*> m_RoomAntList;
    cocos2d::Menu*      m_ActMenu;
    cocos2d::MenuItem*  m_MoveItem;
    cocos2d::MenuItem*  m_OutItem;
	RoomSprite*			m_Sprite;
    int                 m_AntXPos;
    int                 m_AntYPos;
    int                 m_EggXPos;
    int                 m_EggYPos;
    int                 m_SizeX;
    int                 m_SizeY;
    bool                m_IsLeft;
};

#endif

