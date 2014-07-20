/*
 * RecordsManager.cpp
 *
 *  Created on: 18/03/2014
 *      Author: guilhermebraga
 */

#include "RecordsManager.h"

RecordsManager::RecordsManager() {
}

RecordsManager::~RecordsManager() {
}

void RecordsManager::informAltitude(int altitude){
	int points = CCUserDefault::sharedUserDefault()->getIntegerForKey(POINTS_ACCUMULATED, 0);
	if(points < altitude * FACTOR_ALTITUDE_RECORD){
		CCUserDefault::sharedUserDefault()->setIntegerForKey(POINTS_ACCUMULATED, altitude  * FACTOR_ALTITUDE_RECORD);
	}
}

int RecordsManager::getPoints(){
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(POINTS_ACCUMULATED, 0);
}
