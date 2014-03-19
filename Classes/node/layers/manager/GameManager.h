/*
 * GameManager.h
 *
 *  Created on: 17/03/2014
 *      Author: guilhermebraga
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include "../contract/LayerContract.h"
#include "../../sprite/contract/SpriteContract.h"
#include "../../../GameConfig.h"
#include "../../../RecordsManager.h"

class GameManager: public cocos2d::CCObject {
private:
	LayerContract * _layer;
	SpriteContract * _rocket;
	float _speed;
	float rand(void);
	float _factor;
	float _forceTap;
public:
	GameManager(LayerContract * layer);
	virtual ~GameManager();
	CC_SYNTHESIZE(int, _status, Status);
	CC_SYNTHESIZE(float, _altitude, Altitude);
	void init();
    //Actions
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	virtual void update(float dt);
};

#endif /* GAMEMANAGER_H_ */
