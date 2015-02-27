#pragma once
#include "map"
#include "vector"

class Room;
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

    std::map<int, Room*> m_RoomList;
    std::vector<int>     m_RoomDeepList;
};

