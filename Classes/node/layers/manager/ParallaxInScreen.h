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
	float _speed;
public:
	ParallaxInScreen(SpriteContract * sprite);
	virtual ~ParallaxInScreen();
	CC_SYNTHESIZE(SpriteContract *, _sprite, Sprite);
	void display(LayerContract * layer, float width, float scale);
	void move(LayerContract * layer);
	void hide();
	bool isVisible();
};

#endif /* PARALLAXINSCREEN_H_ */
