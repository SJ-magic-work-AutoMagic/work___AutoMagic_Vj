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
: RefreshTime_sec(0.060)
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
		b_Refresh = true;
		t_LastRefresh = now;
	}else{
		b_Refresh = false;
	}
	
}

/******************************
******************************/
void TEXT::draw()
{
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
	if(b_Refresh){
		int DispInTime = int(ofRandom(MIN_DISP_IN_TIME, MAX_DISP_IN_TIME));
		DrawInfo.resize(DispInTime);
		
		for(int i = 0; i < DrawInfo.size(); i++){
			DrawInfo[i].FontSize_id = rand() % NUM_FONT_SIZE;
			DrawInfo[i].pos.set( ofVec2f(rand() % ofGetWidth(), rand() % ofGetHeight()) );
		}
	}
	
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

