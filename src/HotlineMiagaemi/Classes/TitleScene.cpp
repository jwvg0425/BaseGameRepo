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

	m_Image = Sprite::create("title.png");
	auto action = FadeIn::create(2);
	auto callFunc = CallFuncN::create(CC_CALLBACK_1(TitleScene::endAnimation, this));
	auto sequence = Sequence::create(action, callFunc, nullptr);

	m_Image->setOpacity(0);
	m_Image->runAction(sequence);
	m_Image->setAnchorPoint(Point(0, 0));
	m_Image->setPosition(0, 0);

	addChild(m_Image);

	m_Enable = false;
	m_Num = 0;

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TitleScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TitleScene::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void TitleScene::endAnimation(cocos2d::Ref* sender)
{
	m_Enable = true;
}

bool TitleScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	return true;
}

void TitleScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void TitleScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	auto pos = touch->getLocation();
	if (m_Enable && pos.x > 263 && pos.x < 468 && pos.y > 203 && pos.y < 314)
	{
		auto spr = cocos2d::Sprite::create("egg.png");
		spr->setScale(0.5);
		auto move = cocos2d::MoveBy::create(0.3, Point(0, 70));
		auto hide = cocos2d::Hide::create();
		auto action = cocos2d::Sequence::create(move, hide, nullptr);

		spr->setPosition(pos);
		spr->runAction(action);
		addChild(spr);

		m_Num++;

		if (m_Num >= 5)
		{
			m_Enable = false;

			auto delay = DelayTime::create(1);
			auto fade = FadeOut::create(2);
			auto delay2 = DelayTime::create(1);
			auto callback = CallFuncN::create(CC_CALLBACK_1(TitleScene::sceneChange, this));
			auto sequence = Sequence::create(delay, fade, delay2, callback, nullptr);

			m_Image->runAction(sequence);
		}
	}
}

void TitleScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{

}

void TitleScene::sceneChange(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(FosterScene::createScene());
}
