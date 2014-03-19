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
	_altitude = 0;
	_speed = SPEED_START;
	_factor = FACTOR_ANGLE_FORCE;
	_forceTap = TAP_FORCE_START;
}

GameManager::~GameManager() {
}

void GameManager::init() {
	_rocket = Rocket::create(_layer);
	changeToWait();
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
				float force = tap.y * _forceTap / PIXELS_ROWS;
				//X
				if (tap.x > (_layer->getScreenSize().width * 0.50)) {
					//CCLog("X RIGHT %i: ", tap.x);
					_rocket->addAngle(force);
				} else if (tap.x < (_layer->getScreenSize().width * 0.50)) {
					//CCLog("X LEFT %i: ", tap.x);
					_rocket->addAngle(-force);
				}
			}
		}
	}
}

void GameManager::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	if (_status == STATUS_WAIT) {
		_rocket->start();
		_status = STATUS_PLAYING;
		_layer->statusChange(STATUS_PLAYING);
	} else if (_status == STATUS_DIED) {
		changeToWait();
		_layer->statusChange(STATUS_WAIT);
	}
}

void GameManager::changeToWait(){
	_status = STATUS_WAIT;
	_rocket->wait();
	_altitude = 0;
	_speed = SPEED_START;
	_factor = FACTOR_ANGLE_FORCE;
	_forceTap = TAP_FORCE_START;
}

void GameManager::update(float dt) {
	if (_status == STATUS_PLAYING) {
		_altitude += (_speed - ((_rocket->getRotation() < 0 ? _rocket->getRotation() * -1 : _rocket->getRotation()) * (_speed * 0.8f) / 60.0f));
		if (_altitude < 0) {
			_altitude = 0;
		}
		_speed += dt / 100.0f;
		if (_speed > SPEED_MAX) {
			_speed = SPEED_MAX;
		}
		float randValue = rand();
		if (_rocket->getRotation() < MIN_ANGLE || _rocket->getRotation() > MAX_ANGLE) {
			RecordsManager::informAltitude(_altitude);
			_rocket->die();
			_status = STATUS_DIED;
			_layer->statusChange(STATUS_DIED);
		} else if (_rocket->getRotation() > 0) {
			_rocket->addAngle(randValue - _factor < 0 ? 0 : randValue - _factor);
		} else if (_rocket->getRotation() < 0) {
			_rocket->addAngle(-(randValue - _factor < 0 ? 0 : randValue - _factor));
		} else {
			if ((int) rand() % 2 == 0) {
				_rocket->addAngle(randValue);
			} else {
				_rocket->addAngle(-randValue);
			}
		}
		if(_factor >= 0){
			_factor -= dt/10.0f;
		}else {
			_factor += (rand() / 2.0f);
		}

		_forceTap += dt;
		if(_forceTap > TAP_FORCE_MAX){
			_forceTap = TAP_FORCE_MAX;
		}
	}
}

float GameManager::rand(void) {
	static long int next = 1;
	next = next * 1103515245 + 12345;
	int toDivide = (unsigned int) (next / 65536) % 300;
	return toDivide / 100.0f;
}
