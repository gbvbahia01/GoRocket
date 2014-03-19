/*
 * Rocket.h
 *
 *  Created on: 19/03/2014
 *      Author: guilhermebraga
 */

#ifndef ROCKET_H_
#define ROCKET_H_

#include "contract/SpriteContract.h"
#include "../layers/contract/LayerContract.h"

class Rocket: public SpriteContract {
private:
	CCParticleSystem * _tail;
	LayerContract * _layer;

public:
	Rocket(LayerContract * layer);
	virtual ~Rocket();
	static Rocket* create(LayerContract * layer);
	void die();
	void start();
	void wait();
	void addAngle(float angle);
protected:
	virtual void initSprite();
};

#endif /* ROCKET_H_ */
