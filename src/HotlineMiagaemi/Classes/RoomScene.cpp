#include "RoomScene.h"
#include "stdlib.h"

USING_NS_CC;

RoomScene::RoomScene()
{
}


RoomScene::~RoomScene()
{
}

Scene* RoomScene::createScene()
{
    auto scene = Scene::create();

    auto layer = RoomScene::create();

    scene->addChild(layer);

    return scene;
}

bool RoomScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    return true;
}
