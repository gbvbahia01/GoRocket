/*
 * GameManager.cpp
 *
 *  Created on: 17/03/2014
 *      Author: guilhermebraga
 */

#include "GameManager.h"

GameManager::GameManager(LayerContract * layer) {
	_layer = layer;
	_rocket = NULL;
	_status = 0;
}

GameManager::~GameManager() {
}

void GameManager::init() {
	_status = STATUS_WAIT;
	_rocket = SpriteContract::createWithFrameName("rocket.png");
	_rocket->setPosition(ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.20f));
	_rocket->setVisible(true);
	_layer->getGameBatchNode()->addChild(_rocket, kForeground, sprideIdRocket);
}

//Actions
void GameManager::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	if (_status == STATUS_PLAYING) {
		CCSetIterator it;
		CCTouch* touch;
		CCPoint tap;
		for (it = pTouches->begin(); it != pTouches->end(); it++) {
			touch = (CCTouch*) (*it);
			if (touch) {
				tap = touch->getLocation();
				//Y
				float force = 0;
				if (tap.y >= (_layer->getScreenSize().height * 0.66)) {
					force = TAP_FORCE_STRONG;
				} else if (tap.y >= (_layer->getScreenSize().height * 0.33)) {
					force = TAP_FORCE_AVERAGE;
				} else {
					force = TAP_FORCE_WEAK;
				}
				//X
				if (tap.x > (_layer->getScreenSize().width * 0.50)) {
					//CCLog("X RIGHT %i: ", tap.x);
					_rocket->setRotation(_rocket->getRotation() + force);
				} else if (tap.x < (_layer->getScreenSize().width * 0.50)) {
					//CCLog("X LEFT %i: ", tap.x);
					_rocket->setRotation(_rocket->getRotation() - force);
				}
			}
		}
	}
}

void GameManager::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	if (_status == STATUS_WAIT) {
		_status = STATUS_PLAYING;
		_layer->statusChange(STATUS_PLAYING);
	} else if (_status == STATUS_DIED) {
		_status = STATUS_WAIT;
		_layer->statusChange(STATUS_WAIT);
		_rocket->setRotation(0);
	}
}

void GameManager::update(float dt) {
	if (_status == STATUS_PLAYING) {
		if (_rocket->getRotation() < MIN_ANGLE
				|| _rocket->getRotation() > MAX_ANGLE) {
			_status = STATUS_DIED;
			_layer->statusChange(STATUS_DIED);
		} else if (_rocket->getRotation() > 0) {
			_rocket->setRotation(_rocket->getRotation() + rand());
		} else if (_rocket->getRotation() < 0) {
			_rocket->setRotation(_rocket->getRotation() - rand());
		} else {
			if ((int) rand() % 2 == 0) {
				_rocket->setRotation(_rocket->getRotation() + rand());
			} else {
				_rocket->setRotation(_rocket->getRotation() - rand());
			}
		}
	}
}
