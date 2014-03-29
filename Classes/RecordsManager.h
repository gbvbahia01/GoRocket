/*
 * RecordsManager.h
 *
 *  Created on: 18/03/2014
 *      Author: guilhermebraga
 */

#ifndef RECORDSMANAGER_H_
#define RECORDSMANAGER_H_
#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;
class RecordsManager {
public:
	RecordsManager();
	virtual ~RecordsManager();
	static void informAltitude(int altitude);
	static int getPoints();
};

#endif /* RECORDSMANAGER_H_ */
