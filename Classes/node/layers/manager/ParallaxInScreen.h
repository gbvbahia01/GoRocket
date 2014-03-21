/*
 * ParallaxInScreen.h
 *
 *  Created on: 20/03/2014
 *      Author: guilhermebraga
 */

#ifndef PARALLAXINSCREEN_H_
#define PARALLAXINSCREEN_H_
#include "../contract/LayerContract.h"
#include "../../sprite/contract/SpriteContract.h"

class ParallaxInScreen: public cocos2d::CCObject {
private:
	const char *_id;
public:
	ParallaxInScreen(const char *id , float altitude, SpriteContract * sprite);
	virtual ~ParallaxInScreen();
	CC_SYNTHESIZE(bool, _alreadyDisplayed, AlreadyDisplayed);
	CC_SYNTHESIZE(float, _altitude, Altitude);
	CC_SYNTHESIZE(bool, _initShow, InitShow);
	CC_SYNTHESIZE(SpriteContract *, _sprite, Sprite);
	inline const char * getId(){return _id;};

	void display(LayerContract * layer);
	void move(LayerContract * layer);
	void hide();
};

#endif /* PARALLAXINSCREEN_H_ */
