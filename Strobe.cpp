/************************************************************
************************************************************/
#include "Strobe.h"

/************************************************************
************************************************************/

/******************************
******************************/
STROBE::STROBE()
: id(0)
{
}
	
/******************************
******************************/
STROBE::~STROBE()
{
}

/******************************
******************************/
void STROBE::setup()
{
	for(int i = 0; i < NUM_STROBE_TYPE; i++){
		char buf[BUF_SIZE];
		
		sprintf(buf, "Strobe/Strobe_%d.png", i);
		StrobeImage[i].load(buf);
	}
}

/******************************
******************************/
void STROBE::RandomSet_StrobeType()
{
	id = int(rand() % NUM_STROBE_TYPE);
	
	printf("Strobe type = %d.\n", id);
}

/******************************
******************************/
void STROBE::update()
{
}

/******************************
******************************/
void STROBE::draw(double Dj_a)
{
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
	ofSetColor(255, 255, 255, int(Dj_a * 255));
	
	/********************
	********************/
	StrobeImage[id].draw(0, 0, ofGetWidth(), ofGetHeight());
}

/******************************
******************************/
void STROBE::keyPressed(int key)
{
	switch(key){
		case '0':
		{
			id = key - '0';
		}
			break;
	}
	
	printf("return to Normal key\n");
}


