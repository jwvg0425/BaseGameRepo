#include "CutScene.h"

USING_NS_CC;

Scene* CutScene::createScene()
{
    auto scene = Scene::create();

    auto layer = CutScene::create();

    scene->addChild(layer);

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

    auto cutScene = Animate::create(cutAnimation);

    cut1->runAction(cutScene);
    return true;
}
