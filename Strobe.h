/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

#include "sjCommon.h"

/************************************************************
************************************************************/
class STROBE{
private:
	/****************************************
	****************************************/
	struct STROBE_IMAGE{
		ofImage image;
		double Alpha; // 強さを調整したい時は、ここで個別に指定.
	};
	
	/****************************************
	****************************************/
	enum {
		NUM_STROBE_TYPE = 5,
	};
	
	/****************************************
	****************************************/
	STROBE_IMAGE StrobeImage[NUM_STROBE_TYPE];
	int id;
	
    ofxPanel gui;
	ofxFloatSlider Alpha;
	
    bool b_showGui;
	
	
	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	STROBE();
	~STROBE();
	STROBE(const STROBE&); // Copy constructor. no define.
	STROBE& operator=(const STROBE&); // コピー代入演算子. no define.
	
public:
	/****************************************
	****************************************/
	static STROBE* getInstance(){
		static STROBE inst;
		return &inst;
	}
	
	void setup();
	void RandomSet_StrobeType();
	void update();
	void draw(double Dj_a);
	
	void keyPressed(int key);
};


