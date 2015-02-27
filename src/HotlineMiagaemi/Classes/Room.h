#pragma once
class Room
{
public:
    enum RoomType
    {
        RT_NONE,
        RT_EGG,
        RT_QUEEN,
        RT_PRINCESS
    };
    Room();
    virtual ~Room();

    void setYPosition(int yPosition){ m_YPosition = yPosition; }
    bool isLeft(){ return m_IsLeft; }

protected:
    RoomType    m_RoomType;
    bool        m_IsLeft;
    int         m_YPosition;
};

