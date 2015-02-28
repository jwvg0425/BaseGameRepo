#ifndef _TUNNEL_MANAGER_H_
#define _TUNNEL_MANAGER_H_

#define MAX_DEEP -200
#define MIN_ROOM 8
#define MIN_ANT 30
#define MAX_ROOM_INTERVAL 5

#include "RoomScene.h"
#include "cocos2d.h"
#include "map"
#include "vector"

class RoomScene;
class Imago;
class Ant;

class TunnelManager
{
    struct Size
    {
        int x;
        int y;
    };
public:
    static  TunnelManager* getInstance();
    void releaseInstance();
    void initRoom();
    void initAnt();
    bool checkRoomInterval(int yPosition);
    bool checkAntInterval(int antYPos);
    void hallSceneCallback(cocos2d::Ref* sender);
    void roomSceneCallback(int antYPos);
    void moveCallback(int playerX, int playerY);
    bool isAntExist(int playerX, int playerY);
    bool isRoomExist(int antXPos, int antYPos);
    bool isLeft();
	const std::vector<Imago*>& getHallAntList();
	void updateHallAntList();

private:
    TunnelManager();
    virtual ~TunnelManager();
	

    static TunnelManager* m_Instance;

    Ant*                        m_PlayerAnt;
    std::map<int, bool>         m_RoomDirList;
    std::map<int, RoomType>     m_RoomTypeList;
    std::map<int, Size>         m_RoomSizeList;
    std::vector<Imago*>         m_HallAntList;
};

#endif