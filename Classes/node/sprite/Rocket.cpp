/*
 * Rocket.cpp
 *
 *  Created on: 19/03/2014
 *      Author: guilhermebraga
 */

#include "Rocket.h"

Rocket::Rocket(LayerContract * layer) {
	_tail = NULL;
	_boom = NULL;
	_layer = layer;
}

Rocket::~Rocket() {
}

Rocket* Rocket::create(LayerContract * layer) {
	Rocket * rocket = new Rocket(layer);
	if (rocket && rocket->initWithSpriteFrameName("rocket.png")) {
		rocket->setRadius(rocket->boundingBox().size.height * 0.5f);
		rocket->_layer->getGameBatchNode()->addChild(rocket, kForeground, sprideIdRocket);
		rocket->initSprite();
		rocket->setVisible(true);
		return rocket;
	}
	CC_SAFE_DELETE(rocket);
	return NULL;
}

void Rocket::initSprite() {
	_tail = cocos2d::CCParticleSun::create();
	_tail->retain();
	_tail->stopSystem();
	_tail->setAutoRemoveOnFinish(false);
	_tail->setGravity(ccp(0.0f, -200.1f));
	_tail->setStartColor(ORANGE_COLOR);
	_tail->setEndColor(RED_DARCK_COLOR);
	_layer->addChild(_tail, kBackground, spriteIdTail);

	_boom = CCParticleSystemQuad::create("ExplodingRing.plist");
	_boom->retain();
	_boom->stopSystem();
	_boom->setAutoRemoveOnFinish(false);
	_boom->setScale(1.5f);
	_layer->addChild(_boom, kMiddleground, spriteIdBoom);
}

void Rocket::start() {
	_tail->setSourcePosition(ccp(-4,- getRadius() * 0.90f));
	_tail->setAngle(180);
	_tail->setVisible(true);
	_tail->resetSystem();
	runAction(CCMoveTo::create(4.0f,ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.20f)));
	_tail->runAction(CCMoveTo::create(4.0f,ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.10f)));
}

float Rocket::die() {
	stopAllActions();
	_tail->stopSystem();
	_tail->setVisible(false);
	CCAnimation* animation = CCAnimation::create();
	CCSpriteFrame * frame;
	int i;
	for (i = 1; i <= 12; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "rocket_%i.png", i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit((TIME_TO_EXPLODE - 0.5f) / 12);
	animation->setRestoreOriginalFrame(true);
	CCAction* buumAction = CCSequence::create(CCAnimate::create(animation), CCCallFuncN::create(this, callfuncN_selector(Rocket::finishDie)), NULL);
	runAction(buumAction);
	return TIME_TO_EXPLODE;
}

void Rocket::finishDie() {
	setVisible(false);
	_boom->setPosition(getPosition());
	_boom->resetSystem();
}

void Rocket::wait() {
	setVisible(true);
	setPosition(ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.10f));
	setRotation(0);
}

void Rocket::addAngle(float angle) {
	setRotation(getRotation() + angle);
}

void Rocket::update(float dt) {
	_tail->setRotation(getRotation());
	_tail->setPosition(getPosition());
}
