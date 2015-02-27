#include "TitleScene.h"
#include "FosterScene.h"
#include "GameManager.h"

USING_NS_CC;

cocos2d::Scene* TitleScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TitleScene::create();

	scene->addChild(layer);

	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto image = Sprite::create("title.png");
	auto action = FadeIn::create(2);
	auto callFunc = CallFuncN::create(CC_CALLBACK_1(TitleScene::endAnimation, this));
	auto sequence = Sequence::create(action, callFunc, nullptr);

	image->setOpacity(0);
	image->runAction(sequence);
	image->setAnchorPoint(Point(0, 0));
	image->setPosition(0, 0);

	addChild(image);

	m_Enable = false;

	return true;
}

void TitleScene::endAnimation(cocos2d::Ref* sender)
{
	m_Enable = true;
}
