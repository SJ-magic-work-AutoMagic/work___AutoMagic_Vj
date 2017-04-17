/************************************************************
************************************************************/
#include "Text.h"

/************************************************************
************************************************************/
const int FontSize[] = {
	30,
	40,
	50,
	60,
	70,
	80,
	90,
	100,
	110,
	120,
};
const int NUM_FONT_SIZE = sizeof(FontSize) / sizeof(FontSize[0]);

const string Contents[] = {
/*
	"SJ.MAGIC",
	
	"Dj NO+CHIN",
	"Merry X'max",
	
	"FEEL ME",
	"Stop The World",
	"Up to U",
	"Never too late",
	"Nobody's Perfect",
	"Wish me luck",
	"no FUTURE in PAST",
	"No Limit",
*/	
	"SJ.MAGIC",
	
	"TECHNOLOGY",
	"FEEL",
	"Peace",
	"CURIOSITY",
	"Trust No-One",
	"by YOURSELF",
	"Stop The World",
	"EXTREME",
	"GUILTY",
	"Up to U",
	"Never too late",
	"Nobody's Perfect",
	"Wish me luck",
	"Be quick Don't hurry",
	"Problem is Chance",
	"no FUTURE in PAST",
	"find a REMEDY",
	"No Limit",
};
const int NUM_CONTENTS = sizeof(Contents) / sizeof(Contents[0]);

/************************************************************
************************************************************/

/******************************
******************************/
TEXT::TEXT()
// : RefreshTime_sec(0.060)
: RefreshTime_sec(0.500)
, id(0)
{
}

/******************************
******************************/
TEXT::~TEXT()
{
}

/******************************
******************************/
void TEXT::setup()
{
	font.resize(NUM_FONT_SIZE);
	for(int i = 0; i < NUM_FONT_SIZE; i++){
		// font[i].loadFont("RictyDiminished-Regular.ttf", FontSize[i]);
		font[i].loadFont("FTY DELIRIUM NCV.ttf", FontSize[i]);
		// font[i].loadFont("Glamor-Bold.ttf", FontSize[i]);
	}
	
	Refresh_DrawInfo();
}

/******************************
******************************/
void TEXT::set_RefreshRate(int BeatInterval_ms)
{
	RefreshTime_sec = ofMap(BeatInterval_ms, 600/* 100Bpm */, 3000, 0.060, 0.500, true);
}

/******************************
******************************/
void TEXT::update()
{
	/********************
	********************/
	static float t_LastRefresh = 0;
	float now = ofGetElapsedTimef();
	
	if(RefreshTime_sec < now - t_LastRefresh){
		Refresh_DrawInfo();
		
		t_LastRefresh = now;
	}
	
	/********************
	********************/
	static float t_LastINT = 0;
	float dt = ofClamp(now - t_LastINT, 0, 0.1);
	
	for(int i = 0; i < DrawInfo.size(); i++){
		DrawInfo[i].pos.x += DrawInfo[i].speed.x * dt;
		DrawInfo[i].pos.y += DrawInfo[i].speed.y * dt;
	}
	
	t_LastINT = now;
}

/******************************
******************************/
void TEXT::Refresh_DrawInfo()
{
	int DispInTime = int(ofRandom(MIN_DISP_IN_TIME, MAX_DISP_IN_TIME));
	DrawInfo.resize(DispInTime);
	
	for(int i = 0; i < DrawInfo.size(); i++){
		DrawInfo[i].FontSize_id = rand() % NUM_FONT_SIZE;
		DrawInfo[i].pos.set( ofVec2f(rand() % ofGetWidth(), rand() % ofGetHeight()) );
		
		float MaxSpeed = 20;
		DrawInfo[i].speed.set( ofRandom(-MaxSpeed, MaxSpeed), ofRandom(-MaxSpeed, MaxSpeed) );
	}
}

/******************************
******************************/
void TEXT::draw()
{
	float now = ofGetElapsedTimef();

	ofPushStyle();
	
	/********************
	********************/
	// ofBackground(0, 0, 0, 0);
	
	/********************
	********************/
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	/********************
	********************/
	ofSetColor(255, 255, 255, 170);
	for(int i = 0; i < DrawInfo.size(); i++){
		float offset = font[DrawInfo[i].FontSize_id].stringWidth(Contents[id]) / 2;
		font[DrawInfo[i].FontSize_id].drawString(Contents[id], DrawInfo[i].pos.x - offset, DrawInfo[i].pos.y);
	}
	
	ofPopStyle();
}

/******************************
******************************/
void TEXT::RandomSet_Text()
{
	id = rand() % NUM_CONTENTS;
	
	printf("Text = %s\n", Contents[id].c_str());
}

/******************************
******************************/
void TEXT::keyPressed(int key)
{
}

