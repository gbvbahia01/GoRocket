/*
 * SpriteContract.cpp
 *
 *  Created on: 17/03/2014
 *      Author: guilhermebraga
 */

#include "SpriteContract.h"

SpriteContract::SpriteContract() {
	setScreenSize(cocos2d::CCDirector::sharedDirector()->getWinSize());
	_radius = 0;
}

SpriteContract::~SpriteContract() {
}


SpriteContract* SpriteContract::createWithFrameName(const char * pszSpriteFrameName) {
	SpriteContract * sprite = new SpriteContract();
	if (sprite && sprite->initWithSpriteFrameName(pszSpriteFrameName)) {
        sprite->setRadius(sprite->boundingBox().size.width * 0.5f);
        sprite->initSprite();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

//Se tiver animacao na Sprite sobrescreva e implemente
void SpriteContract::initSprite(){
}

bool SpriteContract::morrer(){
	stopAllActions();
	setVisible(false);
	return true;
}

void SpriteContract::update(float dt){
}


