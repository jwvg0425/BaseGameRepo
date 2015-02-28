//À°¼ºÇÏ´Â ¾À

#ifndef __FOSTER_SCENE_H__
#define __FOSTER_SCENE_H__

#include "cocos2d.h"

typedef std::function<void()> ActionFunc;

class StatWindow;
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
	void addUpmoveLabel(float duration, const std::string& text, float height);

	void runAnimation(cocos2d::Sprite* sprite, cocos2d::Animation* animation);

	void feedCallback(cocos2d::Ref* ref);
	void brainwashCallback(cocos2d::Ref* ref);
	void trainCallback(cocos2d::Ref* ref);
	void infiltrateCallback(cocos2d::Ref* ref);

	void battleCallback(cocos2d::Ref* sender);
	void athleticCallback(cocos2d::Ref* sender);
	void exploreCallback(cocos2d::Ref* sender);
	void dodgeCallback(cocos2d::Ref* sender);
	void hellCallback(cocos2d::Ref* sender);

	void setTrainAni();
	void setOriginalAni();

	void battleComplete();
	void athleticComplete();
	void exploreComplete();
	void dodgeComplete();
	void hellComplete();

	void feedComplete();
	void brainwashComplete();

	void startAction(float completeTime, ActionFunc completeActionFunc);
	void completeAction();

	void updateGauge();

	cocos2d::Menu* m_ActMenu;
	cocos2d::MenuItem* m_FeedItem;
	cocos2d::MenuItem* m_BrainWashItem;
	cocos2d::MenuItem* m_TrainItem;
	cocos2d::MenuItem* m_InfiltrateItem;

	//ÈÆ·Ã ¸Þ´º
	cocos2d::Menu* m_TrainMenu;
	cocos2d::Sprite* m_AntSprite;
	cocos2d::Sprite* m_Gaugebar;
	cocos2d::Sprite* m_Gauge;
	cocos2d::Label* m_TypeLabel;
	cocos2d::Label* m_EggNum;

	StatWindow* m_StatWindow;

	ActionFunc m_CompleteActionFunc;

	float m_ActTime;
	float m_CompleteTime;

	bool m_IsAct;
	bool m_IsTrainVisible;
};

#endif // __FOSTER_SCENE_H__
