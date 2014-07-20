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
	CCParticleSystemQuad * _boom;
	LayerContract * _layer;

public:
	Rocket(LayerContract * layer);
	virtual ~Rocket();
	static Rocket* create(LayerContract * layer);
	float die();
	void start();
	void wait();
	void addAngle(float angle);
	void update(float dt);
protected:
	void initSprite();
	void finishDie();
};

#endif /* ROCKET_H_ */
