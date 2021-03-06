#include "AppDelegate.h"
#include "Cutscene.h"
#include "FosterScene.h"
#include "TitleScene.h"
#include "const.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

	srand((unsigned)time(nullptr));

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("HotlineMaigaemi",
			Rect(0,0,WND_WIDTH_CUTSCENE,WND_HEIGHT_CUTSCENE));
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	director->setProjection(Director::Projection::_2D);

    // create a scene. it's an autorelease object
    //auto scene1 = FosterScene::createScene();
    auto scene = CutScene::createScene();
    // run
    //director->runWithScene(scene1);
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
