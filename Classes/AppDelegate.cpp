#include "AppDelegate.h"

USING_NS_CC;
using namespace cocos2d;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    CCSize screenSize = pEGLView->getFrameSize();
    CCSize designSize = CCSize(PIXELS_COLUMNS, PIXELS_ROWS);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);

    //Audio
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename(SOUND_FLYING).c_str());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathForFilename(SOUND_CLICK).c_str());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathForFilename(SOUND_BOOM).c_str());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathForFilename(SOUND_WIND).c_str());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(SOUND_VOLUME);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SOUND_VOLUME);
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
