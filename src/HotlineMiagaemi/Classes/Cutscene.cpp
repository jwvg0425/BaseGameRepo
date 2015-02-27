#include "CutScene.h"
#include "TitleScene.h"

USING_NS_CC;


Scene* CutScene::createScene()
{
    auto scene = Scene::create();

    auto layer = CutScene::create();

    scene->addChild(layer, 0, "CutScene");

    return scene;
}
bool CutScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto cut1 = Sprite::create("cutscene/cut00.png");
    cut1->setAnchorPoint(Vec2(0, 0));
    this->addChild(cut1);
    auto cutAnimation = Animation::create();
    cutAnimation->setDelayPerUnit(2.0f);

	cutAnimation->addSpriteFrameWithFile("cutscene/cut00.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut01.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut02.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut03.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut04.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut05.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut06.png");
	cutAnimation->addSpriteFrameWithFile("cutscene/cut07.png");
	cutAnimation->addSpriteFrameWithFile("cutscene/cut08.png");
	cutAnimation->addSpriteFrameWithFile("cutscene/cut09.png");
	cutAnimation->addSpriteFrameWithFile("cutscene/cut10.png");
	cutAnimation->addSpriteFrameWithFile("cutscene/cut11.png");

    auto director = Director::getInstance();
    auto action1 = Animate::create(cutAnimation);
	auto actionFade = FadeOut::create(2);
    auto action2 = CallFuncN::create(CC_CALLBACK_1(CutScene::SceneCallback, this));
	auto cutScene = Sequence::create(action1, actionFade, action2, NULL);
    cut1->runAction(cutScene);
    return true;
}

void CutScene::SceneCallback(Ref* sender)
{
    Director::getInstance()->replaceScene(TitleScene::createScene());
}
