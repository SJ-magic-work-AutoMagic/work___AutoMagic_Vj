/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sjCommon.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class MOV_EFFECT{
private:
	/****************************************
	****************************************/
	enum EFFECT_TYPE{
		EFFECT_TYPE__SPLIT_5x5,
		
		EFFECT_TYPE__KALEIDOSCOPE,
		EFFECT_TYPE__SPHERE_TEXTURE,
		EFFECT_TYPE__BOX_TEXTURE,
		EFFECT_TYPE__SPLIT_3x3,
		EFFECT_TYPE__SPLIT_2x2,
		
		NUM_EFFECT_TYPE,
	};
	
	/****************************************
	param
	****************************************/
	/********************
	set in RandomSet_EffectType()
	********************/
	EFFECT_TYPE EffectType;
	
	
	/********************
	********************/
	ofShader shader_Kaleido;
	ofShader shader_Split;
	
	/********************
	********************/
	
	ofBoxPrimitive Box;
    ofSpherePrimitive sphere;
	
    ofEasyCam cam;
    ofLight light;
    ofMaterial material;
	
	
	/****************************************
	****************************************/
	void draw_EffectNone(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Kaleido(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_PrimitiveTexture(ofFbo* fbo_src, ofFbo* fbo_dst, EFFECT_TYPE EffectType);
	void draw_Split(ofFbo* fbo_src, ofFbo* fbo_dst, int NumSplit, bool b_InsertNoise);
	
public:
	/****************************************
	****************************************/
	MOV_EFFECT();
	~MOV_EFFECT();
	
	void setup();
	void update();
	void draw(bool b_EffectOn, ofFbo* fbo_src, ofFbo* fbo_dst = NULL);
	
	void RandomSet_EffectType();
	void keyPressed(int key);
};


