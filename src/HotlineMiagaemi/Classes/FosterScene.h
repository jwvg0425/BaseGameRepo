//À°¼ºÇÏ´Â ¾À

#ifndef __FOSTER_SCENE_H__
#define __FOSTER_SCENE_H__

#include "cocos2d.h"

class FosterScene : public cocos2d::LayerColor
{
public:
	FosterScene();
	~FosterScene();

    static cocos2d::Scene* createScene();

    virtual bool init();  

	void update(float dTime);
    
    CREATE_FUNC(FosterScene);

private:
	cocos2d::MenuItem* createActButton(const std::string& labelText, cocos2d::ccMenuCallback callback);
	void setActButtonEnable(cocos2d::MenuItem* item, bool enable);

	void feedCallback(cocos2d::Ref* ref);
	void brainwashCallback(cocos2d::Ref* ref);
	void trainCallback(cocos2d::Ref* ref);
	void infiltrateCallback(cocos2d::Ref* ref);

	void startAction(float completeTime);
	void completeAction();

	void updateGauge();

	cocos2d::Menu* m_ActMenu;
	cocos2d::MenuItem* m_FeedItem;
	cocos2d::MenuItem* m_BrainWashItem;
	cocos2d::MenuItem* m_TrainItem;
	cocos2d::MenuItem* m_InfiltrateItem;
	cocos2d::Sprite* m_AntSprite;
	cocos2d::Sprite* m_Gaugebar;
	cocos2d::Sprite* m_Gauge;

	float m_ActTime;
	float m_CompleteTime;

	bool m_IsAct;
};

#endif // __FOSTER_SCENE_H__
