#include "RoomScene.h"
#include "stdlib.h"

USING_NS_CC;

RoomScene::RoomScene()
{
}


RoomScene::~RoomScene()
{
}

Scene* RoomScene::createScene(RoomType roomType)
{
    auto scene = Scene::create();

    auto layer = RoomScene::create();

    scene->addChild(layer);

    static_cast<RoomScene*>(layer)->setRoomType(roomType);

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
