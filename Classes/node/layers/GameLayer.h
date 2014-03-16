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
#include "../sprite/contract/GameSprite.h"

USING_NS_CC;
//using namespace CocosDenshion;

class GameLayer: public LayerContract {
public:
	GameLayer();
	virtual ~GameLayer();
    static cocos2d::CCScene* scene();
    static GameLayer * create();
    void initLayer();
    //Exit
    void keyBackClicked();

private:
    CCSprite * _bg;
    GameSprite * _rocket;
};

#endif /* GAMELAYER_H_ */
