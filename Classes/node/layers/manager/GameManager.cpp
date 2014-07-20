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
	_meter = NULL;
	_start = NULL;
	_die = NULL;
	_status = 0;
	_altitude = 0;
	_showParallax = false;
	_timeInterStar = 0;
	_timeInterPlanet = 0;
	_factor = FACTOR_ANGLE_START;
	_speed = SPEED_START;
	_forceTap = TAP_FORCE_START;
	_timeWaitDie = 0;
	_planetIndex = 0;
	_parallaxStar = cocos2d::CCArray::createWithCapacity(QTD_STAR_PARALLAX_OBJECTS);
	_parallaxStar->retain();
	_parallaxPlanet = cocos2d::CCArray::createWithCapacity(QTD_PLANET_PARALLAX_OBJECTS);
	_parallaxPlanet->retain();
}

GameManager::~GameManager() {
	CC_SAFE_RELEASE(_parallaxStar);
	CC_SAFE_RELEASE(_parallaxPlanet);
}

void GameManager::init() {
	createParallaxObjects();
	_meter = Meter::create(_layer);
	_rocket = Rocket::create(_layer);
	_start = createSprite("start.png");
	_start->setPosition(ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.37f));
	_die = createSprite("die.png");
	_die->setPosition(ccp(_layer->getScreenSize().width * 0.5f, _layer->getScreenSize().height * 0.37f));
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
				float force = tap.y * _forceTap / (PIXELS_ROWS * 0.7f);
				//X
				if (tap.x > (_layer->getScreenSize().width * 0.50)) {
					//CCLog("X RIGHT %i: ", tap.x);
					_rocket->addAngle(force / FACTOR_APPLY);
				} else if (tap.x < (_layer->getScreenSize().width * 0.50)) {
					//CCLog("X LEFT %i: ", tap.x);
					_rocket->addAngle(-(force / (FACTOR_APPLY) ));
				}
			}
		}
	}
}

void GameManager::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	CCSetIterator it;
	CCTouch* touch;
	CCPoint tap;
	if (_status == STATUS_WAIT) {
		for (it = pTouches->begin(); it != pTouches->end(); it++) {
			touch = (CCTouch*) (*it);
			if (touch) {
				tap = touch->getLocation();
				if (_start->boundingBox().containsPoint(tap)) {
					_rocket->start();
					_start->setVisible(false);
					_meter->start();
					_status = STATUS_PLAYING;
					_layer->statusChange(STATUS_PLAYING);
				}
			}
		}

	} else if (_status == STATUS_DIED) {
		for (it = pTouches->begin(); it != pTouches->end(); it++) {
			touch = (CCTouch*) (*it);
			if (touch) {
				tap = touch->getLocation();
				if (_die->boundingBox().containsPoint(tap)) {
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_CLICK);
					changeToWait();
					_layer->statusChange(STATUS_WAIT);
					_start->setVisible(true);
				}
			}
		}

	}
}

void GameManager::changeToWait() {
	_status = STATUS_WAIT;
	_rocket->wait();
	_meter->wait();
	_altitude = 0;
	_speed = SPEED_START;
	_factor = FACTOR_ANGLE_START;
	_forceTap = TAP_FORCE_START;
	_timeInterStar = 0;
	_timeInterPlanet = 0;
	_timeWaitDie = 0;
	_planetIndex = 0;
	_showParallax = false;
	_start->setVisible(true);
	_die->setVisible(false);
	for (int p = QTD_STAR_PARALLAX_OBJECTS - 1; p >= 0; p--) {
		ParallaxInScreen * parallax = (ParallaxInScreen *) getParallaxStar()->objectAtIndex(p);
		parallax->hide();
	}
	for (int p = QTD_PLANET_PARALLAX_OBJECTS - 1; p >= 0; p--) {
		ParallaxInScreen * parallax = (ParallaxInScreen *) getParallaxPlanet()->objectAtIndex(p);
		parallax->hide();
	}
}

void GameManager::update(float dt) {
	if (_status == STATUS_PLAYING) {
		_altitude += (_speed - ((_rocket->getRotation() < 0 ? (_rocket->getRotation() * FACTOR_APPLY) * -1 : (_rocket->getRotation() * FACTOR_APPLY)) * (_speed * 0.8f) / 60.0f));
		if (_altitude < 0) {
			_altitude = 0;
		}
		updateParallaxObjects(dt);
		_speed += dt / 100.0f;
		if (_speed > SPEED_MAX) {
			_speed = SPEED_MAX;
		}
		float randValue = rand((int) (_factor * 100));
		if ((_rocket->getRotation() * FACTOR_APPLY) < MIN_ANGLE || (_rocket->getRotation() * FACTOR_APPLY) > MAX_ANGLE) {
			RecordsManager::informAltitude(_altitude);
			_timeWaitDie = _rocket->die();
			_status = STATUS_WAIT_DIE;
			_layer->statusChange(STATUS_WAIT_DIE);
		} else if (_rocket->getRotation() > 0) {
			_rocket->addAngle(randValue / FACTOR_APPLY);
		} else if (_rocket->getRotation() < 0) {
			_rocket->addAngle(-(randValue / FACTOR_APPLY));
		} else {
			if ((int) randValue % 2 == 0) {
				_rocket->addAngle(randValue / FACTOR_APPLY);
			} else {
				_rocket->addAngle(-randValue / FACTOR_APPLY);
			}
		}

		if (_factor > FACTOR_ANGLE_MAX) {
			//CCLog("FACTOR IS MAX");
			_factor += (FACTOR_ANGLE_INCREMENT / 10.0f);
		} else {
			_factor += FACTOR_ANGLE_INCREMENT;
		}

		_forceTap += TAP_FORCE_INCREMENT;
		if (_forceTap > TAP_FORCE_MAX) {
			//CCLog("FORCETAP IS MAX");
			_forceTap = TAP_FORCE_MAX;
		}

		_rocket->update(dt);
		_meter->setNeedleAngle(_rocket->getRotation() * FACTOR_APPLY);
	} else if (_status == STATUS_WAIT_DIE) {
		_timeWaitDie -= dt;
		if (_timeWaitDie <= 0) {
			_timeWaitDie = 0;
			_status = STATUS_DIED;
			_die->setVisible(true);
			_layer->statusChange(STATUS_DIED);
		}
	}
}

void GameManager::createParallaxObjects() {
	for (int i = 0; i <= 4; i++) {
		ParallaxInScreen * star1 = new ParallaxInScreen(createSprite("star_1.png"));
		ParallaxInScreen * star2 = new ParallaxInScreen(createSprite("star_2.png"));
		ParallaxInScreen * star3 = new ParallaxInScreen(createSprite("star_3.png"));
		ParallaxInScreen * star4 = new ParallaxInScreen(createSprite("star_4.png"));
		ParallaxInScreen * star5 = new ParallaxInScreen(createSprite("star_5.png"));
		ParallaxInScreen * star6 = new ParallaxInScreen(createSprite("star_6.png"));
		ParallaxInScreen * star7 = new ParallaxInScreen(createSprite("star_7.png"));
		ParallaxInScreen * star8 = new ParallaxInScreen(createSprite("star_8.png"));
		ParallaxInScreen * star9 = new ParallaxInScreen(createSprite("star_9.png"));
		ParallaxInScreen * star10 = new ParallaxInScreen(createSprite("star_10.png"));
		ParallaxInScreen * star11 = new ParallaxInScreen(createSprite("star_11.png"));
		ParallaxInScreen * star12 = new ParallaxInScreen(createSprite("star_12.png"));
		ParallaxInScreen * star13 = new ParallaxInScreen(createSprite("star_13.png"));
		_parallaxStar->addObject(star1);
		_parallaxStar->addObject(star2);
		_parallaxStar->addObject(star3);
		_parallaxStar->addObject(star4);
		_parallaxStar->addObject(star5);
		_parallaxStar->addObject(star6);
		_parallaxStar->addObject(star7);
		_parallaxStar->addObject(star8);
		_parallaxStar->addObject(star9);
		_parallaxStar->addObject(star10);
		_parallaxStar->addObject(star11);
		_parallaxStar->addObject(star12);
		_parallaxStar->addObject(star13);
	}

	ParallaxInScreen * p1 = new ParallaxInScreen(createSprite("mercurio.png"));
	ParallaxInScreen * p2 = new ParallaxInScreen(createSprite("venus.png"));
	ParallaxInScreen * p3 = new ParallaxInScreen(createSprite("terra.png"));
	ParallaxInScreen * p4 = new ParallaxInScreen(createSprite("lua.png"));
	ParallaxInScreen * p5 = new ParallaxInScreen(createSprite("marte.png"));
	ParallaxInScreen * p6 = new ParallaxInScreen(createSprite("jupter.png"));
	ParallaxInScreen * p7 = new ParallaxInScreen(createSprite("saturno.png"));
	ParallaxInScreen * p8 = new ParallaxInScreen(createSprite("uranus.png"));
	ParallaxInScreen * p9 = new ParallaxInScreen(createSprite("netuno.png"));
	ParallaxInScreen * p10 = new ParallaxInScreen(createSprite("plutao.png"));
	_parallaxPlanet->addObject(p1);
	_parallaxPlanet->addObject(p2);
	_parallaxPlanet->addObject(p3);
	_parallaxPlanet->addObject(p4);
	_parallaxPlanet->addObject(p5);
	_parallaxPlanet->addObject(p6);
	_parallaxPlanet->addObject(p7);
	_parallaxPlanet->addObject(p8);
	_parallaxPlanet->addObject(p9);
	_parallaxPlanet->addObject(p10);
}

void GameManager::updateParallaxObjects(float dt) {
	if (_showParallax) {
		for (int p = QTD_STAR_PARALLAX_OBJECTS - 1; p >= 0; p--) {
			ParallaxInScreen * parallax = (ParallaxInScreen *) getParallaxStar()->objectAtIndex(p);
			parallax->move(_layer);
			if (_timeInterStar <= 0) {
				if (!parallax->isVisible()) {
					parallax->display(_layer, rand(100), rand(100));
					_timeInterStar = TIME_INTER_STAR;
				}
			}
		}
		_timeInterStar -= (dt * 100);

		for (int p = QTD_PLANET_PARALLAX_OBJECTS - 1; p >= 0; p--) {
			ParallaxInScreen * parallax = (ParallaxInScreen *) getParallaxPlanet()->objectAtIndex(p);
			parallax->move(_layer);
			if (_timeInterPlanet <= 0 && p == _planetIndex) {
				if (!parallax->isVisible()) {
					parallax->display(_layer, rand(100), rand(80));
					_planetIndex++;
					_timeInterPlanet = TIME_INTER_PLANET;
				}
			}
			if (_planetIndex > QTD_PLANET_PARALLAX_OBJECTS - 1) {
				_planetIndex = 0;
			}
		}
		_timeInterPlanet -= (dt * 100);
	}
}

SpriteContract * GameManager::createSprite(const char * name) {
	SpriteContract * toReturn = SpriteContract::createWithFrameName(name);
	_layer->addChild(toReturn, kBackground, spriteIdBg);
	return toReturn;
}

float GameManager::rand(int factor) {
	static long int next = 1;
	next = next * 1103515245 + 12345;
	int toDivide = (unsigned int) (next / 65536) % factor;
	return toDivide / 100.0f;
}
