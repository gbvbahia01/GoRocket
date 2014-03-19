/*
 * GameLayer.cpp
 *
 *  Created on: 16/03/2014
 *      Author: guilhermebraga
 */

#include "GameLayer.h"

static GameLayer* _instance = NULL;

GameLayer::GameLayer() {
	_bg = NULL;
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
	_bg = CCSprite::create("bg.png");
	_bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * SPACE_X_POSITION_INI));
	_bg->retain();
	this->addChild(_bg, kBackground, spriteIdBg);

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
	if(_gameManager->getStatus() == STATUS_PLAYING){
		if(_bg->getPositionY() > SPACE_X_POSITION_MAX){
			_bg->setPosition(ccp(_screenSize.width * 0.5f, _bg->getPositionY() - (dt * _gameManager->getSpeed() * SPEED_PARALAX_FACTOR)));
		}else {
			_bg->setPosition(ccp(_screenSize.width * 0.5f, SPACE_X_POSITION_MAX));
		}
	}
}

void GameLayer::statusChange(int newStatus) {
	char szName[100] = { 0 };
	switch (newStatus) {
	case STATUS_PLAYING:
		_labelInfo->setString("");
		break;
	case STATUS_DIED:
		_labelInfo->setString("You DIE!");
		sprintf(szName, "Rec: %i", RecordsManager::getPoints());
		_labelRecord->setString(szName);
		break;
	case STATUS_WAIT:
		_labelInfo->setString("Tap to launch");
		_bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * SPACE_X_POSITION_INI));
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
