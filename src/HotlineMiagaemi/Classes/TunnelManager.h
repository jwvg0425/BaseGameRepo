#ifndef _TUNNEL_MANAGER_H_
#define _TUNNEL_MANAGER_H_

#define MAX_DEEP 200
#define MIN_ROOM 4
#define MAX_INTERVAL 10

#include "RoomScene.h"
#include "cocos2d.h"
#include "map"
#include "vector"

class RoomScene;

class TunnelManager
{
public:
    static  TunnelManager* getInstance();
    void releaseInstance();
    void initRoom();
    bool checkRoomInterval(int yPosition);
    void hallSceneCallback(cocos2d::Ref* sender);
    void roomSceneCallback(int antPos);
    bool isRoomExist(int antXPos, int antYPos);
    bool isLeft();

private:
    TunnelManager();
    virtual ~TunnelManager();

    static TunnelManager* m_Instance;

    std::map<int,bool>      m_RoomDirList;
    std::map<int, RoomType> m_RoomTypeList;
};

#endif