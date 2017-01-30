/************************************************************
************************************************************/
#include "movEffect_LineOffsetPerlin.h"

/************************************************************
************************************************************/

/******************************
******************************/
MOV_EFFECT__LINE_OFFSET_PERLIN::MOV_EFFECT__LINE_OFFSET_PERLIN()
: NoiseAmpRatio(0.04)
{
}

/******************************
******************************/
void MOV_EFFECT__LINE_OFFSET_PERLIN::setup()
{
	/********************
	********************/
	shader.load( "movEffect/LineOffsetPerlin/LineOffsetPerlin.vert", "movEffect/LineOffsetPerlin/LineOffsetPerlin.frag");
	
	/********************
	********************/
	for(int i = 0; i < NUM_LINES; i++){
		phase[i] = ofRandom(0, 1000);
	}
}

/******************************
******************************/
void MOV_EFFECT__LINE_OFFSET_PERLIN::update()
{
	float now = ofGetElapsedTimef();
	
	for(int i = 0; i < NUM_LINES; i++){
		offset[i] = NoiseAmpRatio * ofGetWidth() * ofSignedNoise(now * 0.5 + phase[i]);
	}
}

/******************************
******************************/
void MOV_EFFECT__LINE_OFFSET_PERLIN::draw(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	********************/
	ofPushStyle();
	
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
	shader.begin();
	
		/********************
		********************/
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		/********************
		bug : How to send an array to a shader frag on oF0.9.0
			https://forum.openframeworks.cc/t/how-to-send-an-array-to-a-shader-frag-on-of0-9-0/21516/4
			
			when using the underlying OpenGL commands, it works fine.
			
			{
				...
				
				GLuint program = shader.getProgram();
				GLint loc = glGetUniformLocation(program, "offset");
				glUseProgram(program);
				glUniform1fv(loc, NUM_LINES, offset);
				
				...
			}
		********************/
		// shader.setUniform1fv("offset", offset, NUM_LINES);
		GLuint program = shader.getProgram();
		GLint loc = glGetUniformLocation(program, "offset");
		glUseProgram(program);
		glUniform1fv(loc, NUM_LINES, offset);
		
		/********************
		********************/
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader.end();
	fbo_dst_local.end();
	
	/********************
	copy(stretch if needed).
	********************/
	if(fbo_dst){
		fbo_dst->begin();
		
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
		
	}else{
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		fbo_dst_local.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	/********************
	********************/
	ofPopStyle();
}



