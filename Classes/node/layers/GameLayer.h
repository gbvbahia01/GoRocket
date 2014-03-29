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
#include "SimpleAudioEngine.h"
#include "contract/LayerContract.h"
#include "manager/GameManager.h"
#include "../../RecordsManager.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
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
	void gameServicesSignIn();
	//Exit
    void keyBackClicked();

private:
    int _showInterstitialControl;
    CCSprite * _bg1;
    CCSprite * _bg2;
	CCSprite * _soundON;
	CCSprite * _soundOFF;
    SpriteContract * _weakLeft;
    SpriteContract * _weakRight;
    SpriteContract * _strongLeft;
    SpriteContract * _strongRight;
    SpriteContract * _leaderboards;
    SpriteContract * _share;

    GameManager * _gameManager;
    CCLabelTTF * _labelAltitude;
    CCLabelTTF * _labelRecord;
    void showInterstitial();
    void share();
    void blinkTapsIni();
    void blinkTapsEnd( SpriteContract * _sprite);
};

#endif /* GAMELAYER_H_ */
