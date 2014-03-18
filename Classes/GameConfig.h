/*
 * GameConfig.h
 *
 *  Created on: 16/03/2014
 *      Author: guilhermebraga
 */

#ifndef GAMECONFIG_H_
#define GAMECONFIG_H_
//SCREEN
#define PIXELS_COLUMNS 800
#define PIXELS_ROWS 1280

//RULES
#define MAX_ANGLE 60
#define MIN_ANGLE -60
#define TAP_FORCE_STRONG 20.0f
#define TAP_FORCE_AVERAGE 15.0f
#define TAP_FORCE_WEAK 10.0f

enum {
	sprideIdRocket = 1,
	spriteIdCloud
};

enum {
	kBackground = 1,
	kMiddleground,
	kForeground
};

enum {
	STATUS_WAIT = 1,
	STATUS_PLAYING,
	STATUS_DIED

};
#endif /* GAMECONFIG_H_ */
