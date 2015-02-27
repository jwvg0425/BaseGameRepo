#ifndef __HALL_SCENE_H__
#define __HALL_SCENE_H__

#include "cocos2d.h"
typedef std::function<void()> ActionFunc;

class HallScene : public cocos2d::LayerColor
{
public:
    HallScene();
    ~HallScene();

    cocos2d::MenuItem* createActButton(const std::string& labelText, cocos2d::ccMenuCallback callback);

    void setActButtonEnable(cocos2d::MenuItem* item, bool enable);

    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HallScene);

    void moveCallback(cocos2d::Ref* ref);
    void enterCallback(cocos2d::Ref* ref);

private:
    int                 m_AntPos;
    cocos2d::Menu*      m_ActMenu;
    cocos2d::MenuItem*  m_MoveItem;
    cocos2d::MenuItem*  m_EnterItem;
};
#endif
