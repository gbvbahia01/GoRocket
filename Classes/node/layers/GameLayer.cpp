/*
 * GameLayer.cpp
 *
 *  Created on: 16/03/2014
 *      Author: guilhermebraga
 */

#include "GameLayer.h"

static GameLayer* _instance = NULL;

GameLayer::GameLayer() {
	_bg1 = NULL;
	_bg2 = NULL;
	_gameManager = NULL;
	_labelInfo = NULL;
	_labelAltitude = NULL;
	_labelRecord = NULL;
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

	_labelInfo = CCLabelTTF::create("Tap to launch", "Times New Roman", 30);
	_labelInfo->setPosition(ccp(_screenSize.width * 0.2f, _screenSize.height * 0.10f));
	_labelInfo->retain();
	this->addChild(_labelInfo, kMiddleground);

	_labelAltitude = CCLabelTTF::create("0", "Times New Roman", 20);
	_labelAltitude->setPosition(ccp(_screenSize.width * 0.12f, _screenSize.height * 0.075f));
	_labelAltitude->retain();
	this->addChild(_labelAltitude, kMiddleground);

	char szName[100] = { 0 };
	sprintf(szName, "Rec: %i", RecordsManager::getPoints());
	_labelRecord = CCLabelTTF::create(szName, "Times New Roman", 20);
	_labelRecord->setPosition(ccp(_screenSize.width * 0.12f, _screenSize.height * 0.05f));
	_labelRecord->retain();
	this->addChild(_labelRecord, kMiddleground);

	this->scheduleUpdate();

}

//Actions
void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	_gameManager->ccTouchesBegan(pTouches, event);
}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	_gameManager->ccTouchesEnded(pTouches, event);
}

void GameLayer::update(float dt) {
	_gameManager->update(dt);
	char szName[100] = { 0 };
	sprintf(szName, "Alt: %i", ((int) _gameManager->getAltitude() * FACTOR_ALTITUDE_RECORD));
	_labelAltitude->setString(szName);
	if (_gameManager->getStatus() == STATUS_PLAYING) {
		if (_bg2->getPositionY() > _screenSize.height * 0.5f) {
			_bg1->setPosition(ccp(_screenSize.width * 0.5f, _bg1->getPositionY() - (dt * _gameManager->getSpeed() * SPEED_PARALAX_FACTOR)));
			_bg2->setPosition(ccp(_screenSize.width * 0.5f, _bg2->getPositionY() - (dt * _gameManager->getSpeed() * SPEED_PARALAX_FACTOR)));
			if(_bg2->getPositionY() < _screenSize.height * 0.60f){
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
		_labelInfo->setString("");
		break;
	case STATUS_DIED:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		_labelInfo->setString("You DIE!");
		sprintf(szName, "Rec: %i", RecordsManager::getPoints());
		_labelRecord->setString(szName);
		_gameManager->setShowParallax(false);
		break;
	case STATUS_WAIT_DIE:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_BOOM);
		_gameManager->setShowParallax(false);
		break;
	case STATUS_WAIT:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_WIND);
		_labelInfo->setString("Tap to launch");
		_gameManager->setShowParallax(false);
		_bg1->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
		_bg2->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 1.5f));
		break;
		default:
		break;
	}
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
