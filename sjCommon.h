/************************************************************
description
	ofxArtnetにて、common.hが使用されている。
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************************************************
************************************************************/

/********************
********************/
// #define SJ_DEBUG
// #define SJ_REC

/********************
MacのSSD modelの場合、video serverを2つ立てずともloadingが速いので問題なし.

以下条件だと、30fpsでもコマ落ちするケースがあった.
	video server 2つ
	1280 x 720
	MadMapper
	
video serverは3 mov filesを同時に再生しており、CPU 専有率が25 - 35%と非常に大きい.
ので、MacのSSD model使用:video server x 1を基本とする.
********************/
#define ONE_VIDEO_SERVER



/************************************************************
************************************************************/
enum BOOT_MODE{
	MODE_TEST,
	MODE_DEMO,
	
	NUM_MODES,
};

enum{
	BUF_SIZE = 512,
};

enum COLORPATTERNS{
	COLPATTERN_AQUA,
	COLPATTERN_MAGMA,
	COLPATTERN_DIGITAL,
	COLPATTERN_SEXY,
	
	COLPATTERN_TRIP,
	COLPATTERN_REGGAE,
	COLPATTERN_SAMBA,
	COLPATTERN_SWEETS,
	// ↑以上:Autoで使用
	
	/*
	COLPATTERN_RAINBOW,
	COLPATTERN_BLIZZARD,
	
	
	COLPATTERN_AUTO,
	*/
	
	
	NUM_COLORPATTERNS,
};

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
extern BOOT_MODE BootMode;

/************************************************************
************************************************************/
extern void printMessage(const char* message);
extern int Dice_index(int *Weight, int NUM);
