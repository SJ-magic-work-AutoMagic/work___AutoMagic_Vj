/************************************************************
************************************************************/
#include "Strobe.h"

/************************************************************
************************************************************/

/******************************
******************************/
STROBE::STROBE()
: id(0)
, b_showGui(false)
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
	/********************
	********************/
	gui.setup( "Strobe", "Strobe.xml" );
	gui.add( Alpha.setup( "Alpha", 1.0, 0.0, 1.0 ) );
	
	/********************
	********************/
	for(int i = 0; i < NUM_STROBE_TYPE; i++){
		char buf[BUF_SIZE];
		
		sprintf(buf, "Strobe/Strobe_%d.png", i);
		StrobeImage[i].image.load(buf);
		StrobeImage[i].Alpha = 1.0;
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
	if(b_showGui)	ofSetColor(255, 255, 255, int(Dj_a * 255 * Alpha));
	else			ofSetColor(255, 255, 255, int(Dj_a * 255 * StrobeImage[id].Alpha));
	
	/********************
	********************/
	StrobeImage[id].image.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	/********************
	********************/
	if(b_showGui)	gui.draw();
	
	ofPopStyle();
}

/******************************
******************************/
void STROBE::keyPressed(int key)
{
	switch(key){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			int temp = key - '0';
			if(temp < NUM_STROBE_TYPE)	id = temp;
		}
			break;
			
		case 'd':
			b_showGui = !b_showGui;
			break;
	}
	
	printf("return to Normal key\n");
}


