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
#define TAP_FORCE_START 10.0f
#define TAP_FORCE_MAX 50.0f
#define SPEED_START 0.5f
#define SPEED_MAX 1.6
#define FACTOR_ANGLE_FORCE 1.5f

//Ranking
#define POINTS_ACCUMULATED "altitude_accumulated"
#define FACTOR_ALTITUDE_RECORD 10
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
