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

class GameManager: public cocos2d::CCObject {
private:
	LayerContract * _layer;
	SpriteContract * _rocket;
	inline float rand(void){ // RAND_MAX assumed to be 32767
		static long int next = 1;
	    next = next * 1103515245 + 12345;
	    int toDivide = (unsigned int)(next/65536) % 300;
	    return toDivide / 100.0f;
	}
public:
	GameManager(LayerContract * layer);
	virtual ~GameManager();
	CC_SYNTHESIZE(int, _status, Status);
	void init();
    //Actions
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	virtual void update(float dt);
};

#endif /* GAMEMANAGER_H_ */
