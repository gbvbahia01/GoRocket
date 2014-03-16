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
	this->setKeypadEnabled(true);
}

GameLayer::~GameLayer() {
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
	scheduleUpdate();
	_bg = CCSprite::create("bg.png");
	_bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
	this->addChild(_bg);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("art.plist");
	_gameBatchNode = CCSpriteBatchNode::create("art.png");
	_gameBatchNode->retain();
	this->addChild(_gameBatchNode);

	_rocket = GameSprite::createWithFrameName("rocket.png");
	_rocket->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.20f));
	_rocket->setVisible(true);
	_gameBatchNode->addChild(_rocket, kForeground, sprideIdRocket);
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
