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
		EFFECT_TYPE__KALEIDOSCOPE,
		
		EFFECT_TYPE__SPHERE_TEXTURE,
		EFFECT_TYPE__BOX_TEXTURE,
		EFFECT_TYPE__CYLINDER_TEXTURE,
		EFFECT_TYPE__CONE_TEXTURE,
		
		EFFECT_TYPE__SPLIT_2x2,
		EFFECT_TYPE__SPLIT_3x3,
		EFFECT_TYPE__SPLIT_5x5,
		
		EFFECT_TYPE__PARTICLE,
		
		NUM_EFFECT_TYPE,
	};
	
	/****************************************
	param
	****************************************/
	/********************
	set in RandomSet_EffectType()
	********************/
	EFFECT_TYPE EffectType;
	
	static int EffectTypeCombination_id;
	
	
	
	/********************
	********************/
	ofShader shader_Kaleido;
	ofShader shader_Split;
	
	/********************
	********************/
	ofBoxPrimitive Box;
    ofSpherePrimitive sphere;
	ofCylinderPrimitive cylinder;
	ofConePrimitive cone;
	
    ofEasyCam cam;
	bool b_cam_orbit;
	
    ofLight light;
    ofMaterial material;
	
	/********************
	********************/
	enum{
		PARTICLE_WIDTH	= 640,
		PARTICLE_HEIGHT	= 360,
		NUM_PARTICLES	= PARTICLE_WIDTH * PARTICLE_HEIGHT,
	};
	
	ofVbo Vbo;
	ofVec3f Verts[NUM_PARTICLES];
	ofFloatColor Color[NUM_PARTICLES];
	
	
	/****************************************
	****************************************/
	void draw_EffectNone(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Kaleido(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_PrimitiveTexture(ofFbo* fbo_src, ofFbo* fbo_dst, EFFECT_TYPE EffectType);
	void draw_Split(ofFbo* fbo_src, ofFbo* fbo_dst, int NumSplit, bool b_InsertNoise);
	void draw_Particle(ofFbo* fbo_src, ofFbo* fbo_dst);
	
	void Set_EffectType(int id);
	void cam_orbit_motion();
	
public:
	/****************************************
	****************************************/
	enum{
		NUM_EFFECT_TYPE_COMBINATION = NUM_EFFECT_TYPE * NUM_EFFECT_TYPE,
	};
	
	/****************************************
	****************************************/
	MOV_EFFECT();
	~MOV_EFFECT();
	
	void setup();
	void update();
	void draw(bool b_EffectOn, ofFbo* fbo_src, ofFbo* fbo_dst = NULL);
	
	void keyPressed(int key);
	
	static bool IsGray();
	static void RandomSet_EffectType_Combination(MOV_EFFECT& mov, MOV_EFFECT& mov_0);
};


