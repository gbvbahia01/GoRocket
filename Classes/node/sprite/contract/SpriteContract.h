/*
 * SpriteContract.h
 *
 *  Created on: 17/03/2014
 *      Author: guilhermebraga
 */

#ifndef SPRITECONTRACT_H_
#define SPRITECONTRACT_H_

#include "cocos2d.h"
#include "../../../GameConfig.h"

USING_NS_CC;

class SpriteContract: public cocos2d::CCSprite {
public:
	SpriteContract();
	virtual ~SpriteContract();
	CC_SYNTHESIZE(cocos2d::CCSize, _screenSize, ScreenSize);
	CC_SYNTHESIZE(float, _radius, Radius);
	static SpriteContract * createWithFrameName(const char * pszSpriteFrameName);
	virtual bool morrer();
	virtual void update(float dt);
protected:
	virtual void initSprite();
};

#endif /* SPRITECONTRACT_H_ */
