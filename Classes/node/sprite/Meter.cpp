/*
 * Meter.cpp
 *
 *  Created on: 22/03/2014
 *      Author: guilherme
 */

#include "Meter.h"

Meter::Meter(LayerContract * layer) {
	_layer = layer;
	_needle = NULL;
}

Meter::~Meter() {
	CC_SAFE_RELEASE(_needle);
}

Meter* Meter::create(LayerContract * layer) {
	Meter * meter = new Meter(layer);
	if (meter && meter->initWithSpriteFrameName("meter.png")) {
		meter->setRadius(meter->boundingBox().size.height * 0.5f);
		meter->setPosition(ccp(layer->getScreenSize().width * 0.8375f, layer->getScreenSize().height * 0.075f));
		layer->getGameBatchNode()->addChild(meter, kForeground, sprideIdRocket);
		meter->initSprite();
		meter->setVisible(false);
		return meter;
	}
	CC_SAFE_DELETE(meter);
	return NULL;
}

void Meter::initSprite() {
	_needle = SpriteContract::createWithFrameName("needle.png");
	_needle->setVisible(false);
	this->addChild(_needle);
	_needle->retain();
	_needle->setPositionX(_needle->getPositionX() + 128);
	_needle->setPositionY(_needle->getPositionY() + 55);
}

void Meter::wait(){
	setVisible(true);
	_needle->setVisible(true);
	_needle->setRotation(0.0f);
}

void Meter::start(){
}

void Meter::setNeedleAngle(float angle){
	_needle->setRotation(angle);
}
