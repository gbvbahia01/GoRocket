/*
 * LayerContract.cpp
 *
 *  Created on: 09/03/2014
 *      Author: guilhermebraga
 */

#include "LayerContract.h"

LayerContract::LayerContract() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	_gameBatchNode = NULL;
}

LayerContract::~LayerContract() {
}

void LayerContract::initLayer() {
	//Sobrescreva nas Layers
	//Override on Layers
}

void LayerContract::statusChange(int newStatus) {
	//Sobrescreva nas Layers
	//Override on Layers
}
