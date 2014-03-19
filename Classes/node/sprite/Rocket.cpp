/*
 * Rocket.cpp
 *
 *  Created on: 19/03/2014
 *      Author: guilhermebraga
 */

#include "Rocket.h"

Rocket::Rocket(LayerContract * layer) {
	_tail = NULL;
	_layer = layer;
}

Rocket::~Rocket() {
}

Rocket* Rocket::create(LayerContract * layer) {
	Rocket * rocket = new Rocket(layer);
	if (rocket && rocket->initWithSpriteFrameName("rocket.png")) {
		rocket->setRadius(rocket->boundingBox().size.height * 0.5f);
		rocket->_layer->getGameBatchNode()->addChild(rocket);
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
	_layer->addChild(_tail, kBackground, spriteIdTail);
}

void Rocket::start() {
	_tail->setSourcePosition(ccp(-4,- getRadius() * 0.90f));
	_tail->setAngle(180);
	_tail->setVisible(true);
	_tail->resetSystem();
	runAction(CCMoveTo::create(4.0f,ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.20f)));
	_tail->runAction(CCMoveTo::create(4.0f,ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.10f)));
}

void Rocket::die() {
	stopAllActions();
	_tail->stopSystem();
	_tail->setVisible(false);
}

void Rocket::wait() {
	setPosition(ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.10f));
	setRotation(0);
}

void Rocket::addAngle(float angle) {
	setRotation(getRotation() + angle);
	_tail->setRotation(getRotation());
	_tail->setPosition(getPosition());
}
