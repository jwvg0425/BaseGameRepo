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

    m_IsLeft = (rand() % 2) ? true : false;
    int roomType = rand() % 2;
    switch (roomType)
    {
    case 0:
        m_RoomType = RT_EGG;
    case 1:
        m_RoomType = RT_PRINCESS;
    }

    return true;
}
