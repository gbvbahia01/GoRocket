/*
 * GameLayer.cpp
 *
 *  Created on: 16/03/2014
 *      Author: guilhermebraga
 */

#include "GameLayer.h"

static GameLayer* _instance = NULL;

GameLayer::GameLayer() {
	_showInterstitialControl = 0;
	_bg1 = NULL;
	_bg2 = NULL;
	_soundON = NULL;
	_soundOFF = NULL;
	_gameManager = NULL;
	_labelAltitude = NULL;
	_labelRecord = NULL;
	_leaderboards = NULL;
    _weakLeft = NULL;
    _weakRight = NULL;
    _strongLeft = NULL;
    _strongRight = NULL;
    _share = NULL;
	setKeypadEnabled(true);
	setTouchEnabled(true);
}

GameLayer::~GameLayer() {
	CC_SAFE_RELEASE(_gameManager);
}

CCScene* GameLayer::scene() {
	CCScene *scene = CCScene::create();
	GameLayer *layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

GameLayer * GameLayer::create() {
	if (!_instance) {
		_instance = new GameLayer();
	}
	_instance->initLayer();
	return _instance;
}

void GameLayer::initLayer() {
	_bg1 = CCSprite::create("bg1.png");
	_bg1->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
	_bg1->retain();
	this->addChild(_bg1, kBackground, spriteIdBg);

	_bg2 = CCSprite::create("bg2.png");
	_bg2->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 1.5f));
	_bg2->retain();
	this->addChild(_bg2, kBackground, spriteIdBg);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("art.plist");
	_gameBatchNode = CCSpriteBatchNode::create("art.png");
	_gameBatchNode->retain();
	this->addChild(_gameBatchNode, kMiddleground, gameIdBatchNode);

	_gameManager = new GameManager(this);
	_gameManager->init();
	_gameManager->retain();

	 CCSize blockSize = CCSizeMake(100, 50);

	_labelAltitude = CCLabelTTF::create("0", FONT_DIGITAL_NAME, FONT_SIZE, blockSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
	_labelAltitude->setFontFillColor(RED_DARCK_COLOR_3B, true);
	_labelAltitude->setPosition(ccp(_screenSize.width * 0.755f, _screenSize.height * 0.002f));
	_labelAltitude->retain();
	this->addChild(_labelAltitude, kMiddleground);

	char szName[100] = { 0 };
	sprintf(szName, "RC:%i", RecordsManager::getPoints());
	_labelRecord = CCLabelTTF::create(szName, FONT_DIGITAL_NAME, FONT_SIZE, blockSize, kCCTextAlignmentRight, kCCVerticalTextAlignmentTop);
	_labelRecord->setPosition(ccp(_screenSize.width * 0.92f, _screenSize.height * 0.002f));
	_labelRecord->setFontFillColor(ORANGE_COLOR_3B, true);
	_labelRecord->retain();
	this->addChild(_labelRecord, kMiddleground);

	_weakLeft = SpriteContract::createWithFrameName("wl.png");
	_weakLeft->setPosition(ccp(_screenSize.width * 0.1f, _screenSize.height * 0.15f));
	_weakLeft->setVisible(false);
	this->addChild(_weakLeft, kMiddleground);

	_weakRight = SpriteContract::createWithFrameName("wr.png");
	_weakRight->setPosition(ccp(_screenSize.width * 0.9f, _screenSize.height * 0.15f));
	_weakRight->setVisible(false);
	this->addChild(_weakRight, kMiddleground);

	_strongLeft = SpriteContract::createWithFrameName("wsl.png");
	_strongLeft->setPosition(ccp(_screenSize.width * 0.1f, _screenSize.height * 0.70f));
	_strongLeft->setVisible(false);
	this->addChild(_strongLeft, kMiddleground);

	_strongRight = SpriteContract::createWithFrameName("wsr.png");
	_strongRight->setPosition(ccp(_screenSize.width * 0.9f, _screenSize.height * 0.70f));
	_strongRight->setVisible(false);
	this->addChild(_strongRight, kMiddleground);

	_leaderboards = SpriteContract::createWithFrameName("joy.png");
	_leaderboards->setPosition(ccp(_screenSize.width * 0.1f, _screenSize.height * 0.06f));
	if(RecordsManager::getPoints() > 0){
		_leaderboards->setVisible(true);
	}else {
		_leaderboards->setVisible(false);
	}
	this->addChild(_leaderboards, kMiddleground);

	_share = SpriteContract::createWithFrameName("share.png");
	_share->setPosition(ccp(_screenSize.width * 0.3f, _screenSize.height * 0.05f));
	_share->setVisible(true);
	this->addChild(_share, kMiddleground);

	_soundON = CCSprite::createWithSpriteFrameName("sound_on.png");
	_soundON->setPosition(ccp(_screenSize.width * 0.037f, _screenSize.height * 0.978f));
	_soundON->setVisible(CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume() > SOUND_MUTE);
	_soundON->retain();
	this->addChild(_soundON, kForeground);

	_soundOFF = CCSprite::createWithSpriteFrameName("sound_off.png");
	_soundOFF->setPosition(ccp(_screenSize.width * 0.037f, _screenSize.height * 0.978f));
	_soundOFF->setVisible(CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume() == SOUND_MUTE);
	_soundOFF->retain();
	this->addChild(_soundOFF, kForeground);

	this->scheduleUpdate();
	//gameServicesSignIn();
}

//Actions
void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	_gameManager->ccTouchesBegan(pTouches, event);
	if(_gameManager->getStatus() == STATUS_WAIT){
		CCSetIterator it;
		CCTouch* touch;
		CCPoint tap;
		for (it = pTouches->begin(); it != pTouches->end(); it++) {
			touch = (CCTouch*) (*it);
			if (touch) {
				tap = touch->getLocation();
				if (_leaderboards->boundingBox().containsPoint(tap)) {
					gameServicesSignIn();
				}
				if (_share->boundingBox().containsPoint(tap)) {
					share();
				}
			}
		}
	}
}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	_gameManager->ccTouchesEnded(pTouches, event);
	CCTouch *touch = (CCTouch *) pTouches->anyObject();
	if (touch) {
		CCPoint tap = touch->getLocation();
		if (_soundON->boundingBox().containsPoint(tap) || _soundOFF->boundingBox().containsPoint(tap)) {
			if (_soundON->isVisible()) {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(SOUND_MUTE);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SOUND_MUTE);
				_soundON->setVisible(false);
				_soundOFF->setVisible(true);
			} else {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(SOUND_VOLUME);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SOUND_VOLUME);
				_soundON->setVisible(true);
				_soundOFF->setVisible(false);
			}
		}
	}
}

void GameLayer::update(float dt) {
	_gameManager->update(dt);
	char szName[100] = { 0 };
	sprintf(szName, "Al:%i", ((int) _gameManager->getAltitude() * FACTOR_ALTITUDE_RECORD));
	_labelAltitude->setString(szName);
	if (_gameManager->getStatus() == STATUS_PLAYING) {
		if (_bg2->getPositionY() > _screenSize.height * 0.75f) {
				_bg1->setPosition(ccp(_screenSize.width * 0.5f, _bg1->getPositionY() - (dt * _gameManager->getSpeed() * SPEED_PARALAX_FACTOR)));
				_bg2->setPosition(ccp(_screenSize.width * 0.5f, _bg2->getPositionY() - (dt * _gameManager->getSpeed() * SPEED_PARALAX_FACTOR)));
				} else if (_bg2->getPositionY() > _screenSize.height * 0.5f) {
					_bg1->setPosition(ccp(_screenSize.width * 0.5f, _bg1->getPositionY() - (dt * _gameManager->getSpeed() * (SPEED_PARALAX_FACTOR * 0.5f))));
					_bg2->setPosition(ccp(_screenSize.width * 0.5f, _bg2->getPositionY() - (dt * _gameManager->getSpeed() * (SPEED_PARALAX_FACTOR * 0.5f))));
					if(_bg2->getPositionY() < _screenSize.height * 0.65f) {
						_gameManager->setShowParallax(true);
					}
				} else {
					_bg2->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
					_gameManager->setShowParallax(true);
				}
	}
}

void GameLayer::statusChange(int newStatus) {
	char szName[100] = { 0 };
	switch (newStatus) {
	case STATUS_PLAYING:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(SOUND_FLYING, true);
		blinkTapsIni();
		_leaderboards->setVisible(false);
		_share->setVisible(false);
		break;
	case STATUS_DIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		sprintf(szName, "RC:%i", RecordsManager::getPoints());
		_labelRecord->setString(szName);
		_gameManager->setShowParallax(false);
		_leaderboards->setVisible(false);
		_share->setVisible(false);
		showInterstitial();
		break;
	case STATUS_WAIT_DIE:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_BOOM);
		_gameManager->setShowParallax(false);
		_leaderboards->setVisible(false);
		_share->setVisible(false);
		blinkTapsEnd(_strongLeft);
		blinkTapsEnd(_strongRight);
		blinkTapsEnd(_weakLeft);
		blinkTapsEnd(_weakRight);
		break;
	case STATUS_WAIT:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_WIND);
		_gameManager->setShowParallax(false);
		_bg1->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
		_bg2->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 1.5f));
		_leaderboards->setVisible(true);
		_share->setVisible(true);
		break;
		default:
		break;
	}
}

void GameLayer::blinkTapsIni(){
	if(RecordsManager::getPoints() < 3000){
	int timeBlink = 10;
	int blinks = 10;
	CCActionInterval*  actionBlink = CCBlink::create(timeBlink, blinks);
	CCAction* blinkAction = CCSequence::create((CCActionInterval*)actionBlink, CCCallFuncN::create(this, callfuncN_selector(GameLayer::blinkTapsEnd)), NULL);
	_strongLeft->setVisible(true);
	_strongLeft->runAction(blinkAction);
	actionBlink = CCBlink::create(timeBlink, blinks);
	blinkAction = CCSequence::create((CCActionInterval*)actionBlink, CCCallFuncN::create(this, callfuncN_selector(GameLayer::blinkTapsEnd)), NULL);
	_strongRight->setVisible(true);
	_strongRight->runAction(blinkAction);
	actionBlink = CCBlink::create(timeBlink, blinks);
	blinkAction = CCSequence::create((CCActionInterval*)actionBlink, CCCallFuncN::create(this, callfuncN_selector(GameLayer::blinkTapsEnd)), NULL);
	_weakLeft->setVisible(true);
	_weakLeft->runAction(blinkAction);
	actionBlink = CCBlink::create(timeBlink, blinks);
	blinkAction = CCSequence::create((CCActionInterval*)actionBlink, CCCallFuncN::create(this, callfuncN_selector(GameLayer::blinkTapsEnd)), NULL);
	_weakRight->setVisible(true);
	_weakRight->runAction(blinkAction);
	}
}

void GameLayer::blinkTapsEnd( SpriteContract * _sprite){
	_sprite->stopAllActions();
	_sprite->setVisible(false);
}

//Exit game
void GameLayer::keyBackClicked() {
	unscheduleUpdate();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}


void GameLayer::showInterstitial() {
	if(_showInterstitialControl == 3){
		_showInterstitialControl = 0;
	}
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "br/com/mypackage/gorocket/GoRocket",	"showInterstitial", "(I)V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID, ++_showInterstitialControl);
		return;
	}
}

void GameLayer::gameServicesSignIn(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_CLICK);
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "br/com/mypackage/gorocket/GoRocket",	"gameServicesSignIn", "(I)V")) {
		int altitude = RecordsManager::getPoints();
		t.env->CallStaticVoidMethod(t.classID, t.methodID, altitude);
		return;
	}
}

void GameLayer::share() {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_CLICK);
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "br/com/mypackage/gorocket/GoRocket", "share", "(I)Ljava/lang/String;")) {
		int altitude = RecordsManager::getPoints();
		jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID, altitude);
		CCLog((char*) JniHelper::jstring2string(str).c_str());
		return;
	}
}
