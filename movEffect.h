/************************************************************
description


in order to add Effect.
	touch
		movEffect_weight.xlsx.
		void MOV_EFFECT::Set_EffectType(int id)
		
	no need to touch
		mov, mov_0
			Automatically set from "EffectCombination".
			
			
GLSL expression samples
			http://clemz.io/article-retro-shaders-webgl.html
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sjCommon.h"

#include "movEffect_SphereMapping.h"
#include "movEffect_LineOffsetPerlin.h"

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
		
		EFFECT_TYPE__BOXES_MATRIX_TEXTURE,
		EFFECT_TYPE__SPHERES_MATRIX_TEXTURE,
		EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE,
		
		EFFECT_TYPE__SPLIT_2x2,
		EFFECT_TYPE__SPLIT_3x3,
		EFFECT_TYPE__SPLIT_5x5,
		
		EFFECT_TYPE__PARTICLE,
		EFFECT_TYPE__MOSAIC,
		EFFECT_TYPE__NOISE,
		EFFECT_TYPE__SPHERE_MAPPING,
		
		EFFECT_TYPE__MIRROR_LR,
		EFFECT_TYPE__MIRROR_VERT,
		
		EFFECT_TYPE__LINE_OFFSET_PERLINE,
		
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
	ofShader shader_Mosaic;
	ofShader shader_Noise;
	ofShader shader_Mirror_LR;
	ofShader shader_Mirror_Vert;
	
	/********************
	kaleido scope
	********************/
	float k_angle;
	
	/********************
	********************/
	ofBoxPrimitive Box;
    ofSpherePrimitive sphere;
	ofCylinderPrimitive cylinder;
	ofConePrimitive cone;
	
    ofEasyCam cam;
	bool b_cam_orbit;
	bool b_cam_Enable_MouseInput;
	
    ofLight light;
    ofMaterial material;
	
	/********************
	********************/
	enum{
/*
		// Particle:small
		PARTICLE_WIDTH	= 160,
		PARTICLE_HEIGHT	= 90,
*/		

		// Particle:middle
		PARTICLE_WIDTH	= 320,
		PARTICLE_HEIGHT	= 180,
		
/*
		// Particle:Large
		PARTICLE_WIDTH	= 640,
		PARTICLE_HEIGHT	= 360,
*/
		NUM_PARTICLES	= PARTICLE_WIDTH * PARTICLE_HEIGHT,
	};
	
	ofVbo Vbo;
	ofVec3f Verts[NUM_PARTICLES];
	ofFloatColor Color[NUM_PARTICLES];
	
	/********************
	********************/
	MOV_EFFECT__SPHERE_MAPPING SphereMapping;
	MOV_EFFECT__LINE_OFFSET_PERLIN LineOffset_Perlin;
	
	/****************************************
	****************************************/
	void draw_EffectNone(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Kaleido(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_PrimitiveTexture(ofFbo* fbo_src, ofFbo* fbo_dst, EFFECT_TYPE EffectType);
	void draw_Split(ofFbo* fbo_src, ofFbo* fbo_dst, int NumSplit);
	void draw_Particle(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Mosaic(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Noise(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Mirror_LR(ofFbo* fbo_src, ofFbo* fbo_dst);
	void draw_Mirror_Vert(ofFbo* fbo_src, ofFbo* fbo_dst);
	
	void Set_EffectType(int id);
	void cam_orbit_motion();
	
	void draw_BoxMatrix();
	void draw_SphereMatrix();
	void draw_CylinderMatrix();
	
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


