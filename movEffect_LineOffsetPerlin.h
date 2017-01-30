/************************************************************
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
	
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sjCommon.h"

/************************************************************
************************************************************/

class MOV_EFFECT__LINE_OFFSET_PERLIN{
private:
	/****************************************
	****************************************/
	const double NoiseAmpRatio;
	
	ofShader shader;
	
	enum{
		/********************
		********************/
		NUM_LINES = 256,
	};
	float phase[NUM_LINES];
	float offset[NUM_LINES];
	
	
public:
	/****************************************
	****************************************/
	MOV_EFFECT__LINE_OFFSET_PERLIN();
	
	void setup();
	void update();
	void draw(ofFbo* fbo_src, ofFbo* fbo_dst);
};

