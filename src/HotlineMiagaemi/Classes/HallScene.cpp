#include "HallScene.h"

USING_NS_CC;

HallScene::HallScene()
{
}


HallScene::~HallScene()
{
}

Scene* HallScene::createScene()
{
    auto scene = Scene::create();

    auto layer = HallScene::create();

    scene->addChild(layer);

    return scene;
}

bool HallScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    return true;
}
