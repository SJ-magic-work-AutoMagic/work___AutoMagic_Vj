/************************************************************
************************************************************/
#include "Text.h"

/************************************************************
************************************************************/
const int FontSize[] = {
	10,
	20,
	30,
	40,
	50,
	60,
	70,
	80,
	90,
	100,
};
const int NUM_FONT_SIZE = sizeof(FontSize) / sizeof(FontSize[0]);

const string Contents[] = {
	"SAIJO",
	"NOBUHIRO",
	"TIESTO",
};
const int NUM_CONTENTS = sizeof(Contents) / sizeof(Contents[0]);

/************************************************************
************************************************************/

/******************************
******************************/
TEXT::TEXT()
: RefreshTime_sec(0.060)
,  id(0)
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
		font[i].loadFont("RictyDiminished-Regular.ttf", FontSize[i]);
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
	/********************
	********************/
	if(b_Refresh){
		int DispInTime = rand() % MAX_DISP_IN_TIME;
		DrawInfo.resize(DispInTime);
		
		for(int i = 0; i < DrawInfo.size(); i++){
			DrawInfo[i].FontSize_id = rand() % NUM_FONT_SIZE;
			DrawInfo[i].pos.set( ofVec2f(rand() % ofGetWidth(), rand() % ofGetHeight()) );
		}
	}
	
	ofSetColor(255, 255, 255, 150);
	for(int i = 0; i < DrawInfo.size(); i++){
		font[DrawInfo[i].FontSize_id].drawString(Contents[id], DrawInfo[i].pos.x, DrawInfo[i].pos.y);
	}
}

/******************************
******************************/
void TEXT::RandomSet_Text()
{
	id = rand() % NUM_CONTENTS;
}

/******************************
******************************/
void TEXT::keyPressed(int key)
{
}

