/*
 * GameManager.h
 *
 *  Created on: 17/03/2014
 *      Author: guilhermebraga
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "SimpleAudioEngine.h"
#include "ParallaxInScreen.h"
#include "../contract/LayerContract.h"
#include "../../sprite/Meter.h"
#include "../../sprite/Rocket.h"
#include "../../../GameConfig.h"
#include "../../../RecordsManager.h"

class GameManager: public cocos2d::CCObject {
private:
	LayerContract * _layer;
	Rocket * _rocket;
	Meter * _meter;
    SpriteContract * _start;
    SpriteContract * _die;

	float rand(int factorMax);
	float _factor;
	float _forceTap;
	float _timeWaitDie;
	float _timeInterStar;
	float _timeInterPlanet;
	int _planetIndex;
	void changeToWait();
	void createParallaxObjects();
	void updateParallaxObjects(float dt);
	SpriteContract * createSprite(const char * name);
public:
	GameManager(LayerContract * layer);
	virtual ~GameManager();
	CC_SYNTHESIZE(int, _status, Status);
	CC_SYNTHESIZE(bool, _showParallax, ShowParallax);
	CC_SYNTHESIZE(float, _altitude, Altitude);
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(cocos2d::CCArray *, _parallaxStar, ParallaxStar);
	CC_SYNTHESIZE(cocos2d::CCArray *, _parallaxPlanet, ParallaxPlanet);
	void init();
    //Actions
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	virtual void update(float dt);
};

#endif /* GAMEMANAGER_H_ */
