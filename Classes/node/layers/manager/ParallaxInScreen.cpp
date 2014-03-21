/*
 * ParallaxInScreen.cpp
 *
 *  Created on: 20/03/2014
 *      Author: guilhermebraga
 */

#include "ParallaxInScreen.h"

ParallaxInScreen::ParallaxInScreen(const char *id, float altitude, SpriteContract * sprite) {
	_id = id;
	_sprite = sprite;
	_alreadyDisplayed = false;
	_altitude = altitude;
	if(_id == ID_SUN_PARALLAX || _id == ID_CLOUD1_PARALLAX || _id == ID_CLOUD2_PARALLAX || _id == ID_CLOUD3_PARALLAX){
		_initShow = true;
	}else {
		_initShow = false;
	}
}

ParallaxInScreen::~ParallaxInScreen() {
}

void ParallaxInScreen::display(LayerContract * layer) {
	if (_id == ID_SUN_PARALLAX) {
		_sprite->setPosition(ccp(layer->getScreenSize().width * 0.2f, layer->getScreenSize().height * 0.90f));
	}else if(_id == ID_CLOUD1_PARALLAX) {
		_sprite->setPosition(ccp(layer->getScreenSize().width * 0.25f, layer->getScreenSize().height * 0.50f));
	}else if(_id == ID_CLOUD2_PARALLAX) {
		_sprite->setPosition(ccp(layer->getScreenSize().width * 0.5f, layer->getScreenSize().height * 0.45f));
	}else if(_id == ID_CLOUD3_PARALLAX) {
		_sprite->setPosition(ccp(layer->getScreenSize().width * 0.75f, layer->getScreenSize().height * 0.40f));
	}else if(_id == ID_MOON_PARALLAX) {
		_sprite->setPosition(ccp(layer->getScreenSize().width * 0.8f, layer->getScreenSize().height * 1.2f));
	}
	_sprite->setVisible(true);
	_alreadyDisplayed = true;
}

void ParallaxInScreen::move(LayerContract * layer) {
	if (_alreadyDisplayed && _sprite->isVisible()) {
		_sprite->setPosition(ccp(_sprite->getPositionX(), _sprite->getPositionY() - (SPEED_PARALAX_FACTOR / 10)));
	}
	if(_alreadyDisplayed && _sprite->isVisible() && _sprite->getPositionY() < -(layer->getScreenSize().height * 0.2f)) {
		hide();
	}
}

void ParallaxInScreen::hide() {
	_sprite->setVisible(false);
}
