/*
 * LayerContract.h
 *
 *  Created on: 09/03/2014
 *      Author: guilhermebraga
 */

#ifndef LAYERCONTRACT_H_
#define LAYERCONTRACT_H_
#include "cocos2d.h"

USING_NS_CC;

class LayerContract: public cocos2d::CCLayer {
public:
	LayerContract();
	virtual ~LayerContract();
	CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, _gameBatchNode, GameBatchNode);
	CC_SYNTHESIZE(cocos2d::CCSize, _screenSize, ScreenSize);

protected:
	virtual void initLayer();
};

#endif /* LAYERCONTRACT_H_ */
