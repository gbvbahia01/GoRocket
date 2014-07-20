/*
 * Meter.h
 *
 *  Created on: 22/03/2014
 *      Author: guilherme
 */

#ifndef METER_H_
#define METER_H_

#include "../layers/contract/LayerContract.h"
#include "contract/SpriteContract.h"

class Meter: public SpriteContract {
private:
	LayerContract * _layer;
	SpriteContract * _needle;
public:
	Meter(LayerContract * layer);
	virtual ~Meter();
	static Meter* create(LayerContract * layer);
	void wait();
	void start();
	void setNeedleAngle(float angle);
protected:
void initSprite();

};

#endif /* METER_H_ */
