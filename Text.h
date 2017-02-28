/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sjCommon.h"

/************************************************************
************************************************************/
class TEXT{
private:
	/****************************************
	****************************************/
	struct DRAW_INFO{
		int FontSize_id;
		ofVec2f pos;
	};
	
	/****************************************
	****************************************/
	enum{
		MIN_DISP_IN_TIME = 4,
		MAX_DISP_IN_TIME = 10,
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
	double RefreshTime_sec;
	
	/********************
	********************/
	int id;
	vector<ofTrueTypeFont> font;
	
	bool b_Refresh;
	
	vector<DRAW_INFO> DrawInfo;
	
	
	
	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	TEXT();
	~TEXT();
	TEXT(const TEXT&); // Copy constructor. no define.
	TEXT& operator=(const TEXT&); // コピー代入演算子. no define.
	
public:
	/****************************************
	****************************************/
	static TEXT* getInstance(){
		static TEXT inst;
		return &inst;
	}
	
	void setup();
	void set_RefreshRate(int BeatInterval_ms);
	void update();
	void draw();
	
	void RandomSet_Text();
	
	void keyPressed(int key);
};

