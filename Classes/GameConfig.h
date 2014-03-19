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

//Control
#define TIME_TO_EXPLODE 1.5f
#define SPACE_X_POSITION_INI 1.17f
#define SPACE_X_POSITION_MAX -218.0f
#define SPEED_PARALAX_FACTOR 15

//Colors
#define YELLOW_COLOR ccc4f(0.9f, 0.89f, 0.3f, 1.0f)
#define ORANGE_COLOR ccc4f(0.88f, 0.53f, 0.06f, 1.0f)
#define RED_DARCK_COLOR ccc4f(0.57f, 0.1f, 0.0f, 1.0f)

enum {
	sprideIdRocket = 1,
	spriteIdTail,
	spriteIdBoom,
	gameIdBatchNode,
	spriteIdCloud,
	spriteIdBg,
};

enum {
	kBackground = 1,
	kMiddleground,
	kForeground
};

enum {
	STATUS_WAIT = 1,
	STATUS_PLAYING,
	STATUS_WAIT_DIE,
	STATUS_DIED

};
#endif /* GAMECONFIG_H_ */
