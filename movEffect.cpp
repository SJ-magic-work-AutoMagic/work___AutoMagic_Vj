/************************************************************
************************************************************/
#include "movEffect.h"

/************************************************************
************************************************************/

/******************************
******************************/
MOV_EFFECT::MOV_EFFECT()
: EffectType(EFFECT_TYPE__KALEIDOSCOPE)
{
}

/******************************
******************************/
MOV_EFFECT::~MOV_EFFECT()
{
}

/******************************
******************************/
void MOV_EFFECT::RandomSet_EffectType()
{
	EffectType = EFFECT_TYPE(rand() % NUM_EFFECT_TYPE);
	
	printf("mov type = %d.\n", EffectType);
	
	
	
}

/******************************
******************************/
void MOV_EFFECT::setup()
{
	/********************
	********************/
	shader_Kaleido.load( "movEffect/Kaleido/kaleido.vert", "movEffect/Kaleido/kaleido.frag");
	shader_Split.load( "movEffect/Split/Split.vert", "movEffect/Split/Split.frag");
	
	/********************
	********************/
    sphere.set(250, 80);
    sphere.rotate(180, 0, 1, 0);
	
	Box.set(300);
}

/******************************
******************************/
void MOV_EFFECT::update()
{
    sphere.set(ofGetWidth() * 0.18, 80);
	Box.set(ofGetWidth() * 0.2);
}

/******************************
description
param
	fbo_dst
		NULL : draw to screen.
******************************/
void MOV_EFFECT::draw(bool b_EffectOn, ofFbo* fbo_src, ofFbo* fbo_dst)
{
	if(b_EffectOn){
		switch(EffectType){
			case EFFECT_TYPE__KALEIDOSCOPE:
				draw_Kaleido(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__SPHERE_TEXTURE:
				draw_PrimitiveTexture(fbo_src, fbo_dst, EFFECT_TYPE__SPHERE_TEXTURE);
				break;
				
			case EFFECT_TYPE__BOX_TEXTURE:
				draw_PrimitiveTexture(fbo_src, fbo_dst, EFFECT_TYPE__BOX_TEXTURE);
				break;
				
			case EFFECT_TYPE__SPLIT_3x3:
				draw_Split(fbo_src, fbo_dst, 3, true);
				break;
				
			case EFFECT_TYPE__SPLIT_2x2:
				draw_Split(fbo_src, fbo_dst, 2, true);
				break;
				
			case EFFECT_TYPE__SPLIT_5x5:
				draw_Split(fbo_src, fbo_dst, 5, true);
				break;
				
			default:
				draw_EffectNone(fbo_src, fbo_dst);
				break;
		}
		
	}else{
		draw_EffectNone(fbo_src, fbo_dst);
	}
}

/******************************
******************************/
void MOV_EFFECT::draw_Split(ofFbo* fbo_src, ofFbo* fbo_dst, int NumSplit, bool b_InsertNoise)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGBA);
	
	fbo_dst_local.begin();
	shader_Split.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
		shader_Split.setUniform2f( "screenSize", fbo_dst_local.getWidth(), fbo_dst_local.getHeight() );
		shader_Split.setUniform1i( "NumSplit", NumSplit);
		
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader_Split.end();
	fbo_dst_local.end();
	
	/********************
	copy(stretch if needed).
	********************/
	if(fbo_dst){
		fbo_dst->begin();
		
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
	}else{
		fbo_dst_local.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

/******************************
******************************/
void MOV_EFFECT::draw_PrimitiveTexture(ofFbo* fbo_src, ofFbo* fbo_dst, EFFECT_TYPE EffectType)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGBA);
	
	switch(EffectType){
		case EFFECT_TYPE__SPHERE_TEXTURE:
			sphere.mapTexCoords(0, fbo_src->getHeight(), fbo_src->getWidth(), 0);
			break;
		case EFFECT_TYPE__BOX_TEXTURE:
			Box.mapTexCoords(0, fbo_src->getHeight(), fbo_src->getWidth(), 0);
			break;
	}
	
	ofEnableDepthTest();
	fbo_dst_local.begin();
		fbo_src->getTextureReference().bind();
		
		//Camera automation
		//Comment this block to control camera with mouse
		//(Note: also, you need to disable GUI by pressing Z
		//to enable camera controlling with mouse)
		float time = ofGetElapsedTimef();
		float longitude = 15 * time; // rotation speed
		float latitude = ofGetWidth() * 0.015 * sin(time*0.8); // y方向に軽く揺らす.
		float radius = ofGetWidth() * 0.4 + ofGetWidth() * 0.04 * sin(time*0.4);
		cam.orbit( longitude, latitude, radius, ofPoint(0,0,0) );
		
		cam.begin();
			/*
			// comment out light so that the face get brighter.
			// light.setPosition(ofGetWidth()/2, ofGetHeight()/2, 600);
			// light.setPosition(fbo_dst_local.getWidth()/4, fbo_dst_local.getHeight()/4, 600);
			// light.enable();
			*/
			material.begin();
			
			ofBackground(0, 0, 0, 0);
			ofSetColor(255, 255, 255, 255);
			ofEnableAlphaBlending();
			
			switch(EffectType){
				case EFFECT_TYPE__SPHERE_TEXTURE:
					sphere.draw();
					break;
				case EFFECT_TYPE__BOX_TEXTURE:
					Box.draw();
					break;
			}
		cam.end();
		
		
		ofDisableDepthTest();
		material.end();
		// light.disable();
		// ofDisableLighting();
		
		fbo_src->getTextureReference().unbind();
	fbo_dst_local.end();
	
	/********************
	copy(stretch if needed).
	********************/
	if(fbo_dst){
		fbo_dst->begin();
		
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
	}else{
		fbo_dst_local.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

/******************************
******************************/
void MOV_EFFECT::draw_Kaleido(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGBA);
	
	fbo_dst_local.begin();
	shader_Kaleido.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
		shader_Kaleido.setUniform2f( "screenCenter", fbo_dst_local.getWidth()/2, fbo_dst_local.getHeight()/2 );
		shader_Kaleido.setUniform2f( "kcenter", fbo_src->getWidth()/2, fbo_src->getHeight()/2 );
		shader_Kaleido.setUniform1i( "ksectors", 10 );
		// shader_Kaleido.setUniform1f( "kangleRad", ofDegToRad(k_angle) );
		shader_Kaleido.setUniform1f( "kangleRad", 0 );
		shader_Kaleido.setUniform1f( "alpha", 1.0 );
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader_Kaleido.end();
	fbo_dst_local.end();
	
	/********************
	copy(stretch if needed).
	********************/
	if(fbo_dst){
		fbo_dst->begin();
		
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
	}else{
		fbo_dst_local.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

/******************************
description

assume
	fbo_src & fbo_dst have same size.
******************************/
void MOV_EFFECT::draw_EffectNone(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	if(fbo_dst){
		fbo_dst->begin();
		
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
		fbo_src->draw(0, 0);
		
		fbo_dst->end();
	}else{
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		fbo_src->draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

/******************************
******************************/
void MOV_EFFECT::keyPressed(int key)
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
		{
			EffectType = EFFECT_TYPE(key - '0');
		}
			break;
			
		case 'd':
			// showGui = !showGui;
			break;
			
		case 's':
			// if(showGui) gui.saveToFile("indicator.xml");
			break;
	}
	
	printf("return to Normal key\n");
}

