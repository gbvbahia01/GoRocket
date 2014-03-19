/*
 * GameLayer.h
 *
 *  Created on: 16/03/2014
 *      Author: guilhermebraga
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
#include "../../GameConfig.h"
//#include "SimpleAudioEngine.h"
#include "contract/LayerContract.h"
#include "manager/GameManager.h"
#include "../../RecordsManager.h"

USING_NS_CC;
//using namespace CocosDenshion;

class GameLayer: public LayerContract {
public:
	GameLayer();
	virtual ~GameLayer();
    static cocos2d::CCScene* scene();
    static GameLayer * create();
    void initLayer();
    //Actions
	void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	void update(float dt);
	void statusChange(int newStatus);
    //Exit
    void keyBackClicked();

private:
    CCSprite * _bg;
    GameManager * _gameManager;
    CCLabelTTF * _labelInfo;
    CCLabelTTF * _labelAltitude;
    CCLabelTTF * _labelRecord;
};

#endif /* GAMELAYER_H_ */
