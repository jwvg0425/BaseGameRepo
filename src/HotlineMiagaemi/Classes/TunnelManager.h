#pragma once
#include "RoomScene.h"
#include "map"
#include "vector"

class RoomScene;

class TunnelManager
{
public:
    static  TunnelManager* getInstance();
    void releaseInstance();
    void initRoom();
    bool CheckRoomInterval(int yPosition);

private:
    TunnelManager();
    virtual ~TunnelManager();

    static TunnelManager* m_Instance;

    std::map<int,bool>      m_RoomDirList;
    std::map<int, RoomType> m_RoomTypeList;
    int                     m_AntDeep;
};

