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
#define TAP_FORCE_START 5.0f
#define TAP_FORCE_MAX 50.0f
#define TAP_FORCE_INCREMENT 0.001f
#define FACTOR_ANGLE_START 1.0f
#define FACTOR_ANGLE_MAX 5.0f
#define FACTOR_ANGLE_INCREMENT 0.0005f
#define SPEED_START 0.5f
#define SPEED_MAX 1.6


//Ranking
#define POINTS_ACCUMULATED "altitude_accumulated"
#define FACTOR_ALTITUDE_RECORD 10

//Control
#define TIME_TO_EXPLODE 1.5f

//Parallax Control
#define QTD_STAR_PARALLAX_OBJECTS 65
#define QTD_PLANET_PARALLAX_OBJECTS 10
#define SPEED_PARALAX_FACTOR 50
#define TIME_INTER_STAR 10
#define TIME_INTER_PLANET 1500

//Colors
#define YELLOW_COLOR ccc4f(0.9f, 0.89f, 0.3f, 1.0f)
#define ORANGE_COLOR ccc4f(0.88f, 0.53f, 0.06f, 1.0f)
#define RED_DARCK_COLOR ccc4f(0.57f, 0.1f, 0.0f, 1.0f)
#define RED_DARCK_COLOR_3B ccRED
#define ORANGE_COLOR_3B ccORANGE
//Sound
#define SOUND_CLICK "click.ogg"
#define SOUND_BOOM "boom.ogg"
#define SOUND_WIND "wind.ogg"
#define SOUND_FLYING "flying.ogg"
#define SOUND_VOLUME 0.5f
#define SOUND_MUTE 0.0

//Font
#define FONT_SIZE 20
#define FONT_NAME "fonts/AARDC___.ttf"
#define FONT_DIGITAL_NAME "fonts/DS-DIGIB.ttf"

enum {
	sprideIdRocket = 1,
	spriteIdTail,
	spriteIdBoom,
	gameIdBatchNode,
	spriteId,
	spriteIdBg
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
