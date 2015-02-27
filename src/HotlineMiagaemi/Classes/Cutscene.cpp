#include "CutScene.h"
#include "FosterScene.h"

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

    auto cut1 = Sprite::create("cutscene/cut1.png");
    cut1->setPosition(Vec2(100.0f, 20.0f));
    cut1->setAnchorPoint(Vec2(0, 0));
    this->addChild(cut1);
    auto cutAnimation = Animation::create();
    cutAnimation->setDelayPerUnit(3.0f);

    cutAnimation->addSpriteFrameWithFile("cutscene/cut1.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut2.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut3.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut4.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut5.png");
    cutAnimation->addSpriteFrameWithFile("cutscene/cut6.png");

    auto director = Director::getInstance();
    auto action1 = Animate::create(cutAnimation);
    auto action2 = CallFuncN::create(CC_CALLBACK_1(CutScene::SceneCallback, this));
    auto cutScene = Sequence::create(action1, action2, NULL);
    cut1->runAction(cutScene);
    return true;
}

void CutScene::SceneCallback(Ref* sender)
{
    Director::getInstance()->replaceScene(FosterScene::createScene());
}
