/*
 * ParallaxInScreen.cpp
 *
 *  Created on: 20/03/2014
 *      Author: guilhermebraga
 */

#include "ParallaxInScreen.h"

ParallaxInScreen::ParallaxInScreen(SpriteContract * sprite) {
	_sprite = sprite;
	_speed = 0.0f;
}

ParallaxInScreen::~ParallaxInScreen() {
}

void ParallaxInScreen::display(LayerContract * layer, float width, float scale) {
	if(width > 1){
		CCLog("width > 1 %i", width);
	}else if(width < 0){
		CCLog("width < 0 %i", width);
	}
	_sprite->setPosition(ccp(layer->getScreenSize().width * width, layer->getScreenSize().height * 1.20f));
	_sprite->setScale(scale);
	_sprite->setVisible(true);
	_speed = SPEED_PARALAX_FACTOR * scale;
}

void ParallaxInScreen::move(LayerContract * layer) {
	if (_sprite->isVisible()) {
		_sprite->setPosition(ccp(_sprite->getPositionX(), _sprite->getPositionY() - (_speed / 10)));
	}
	if(_sprite->isVisible() && _sprite->getPositionY() < -(layer->getScreenSize().height * 0.2f)) {
		hide();
	}
}

void ParallaxInScreen::hide() {
	_sprite->setVisible(false);
}

bool ParallaxInScreen::isVisible(){
	return _sprite->isVisible();
}
