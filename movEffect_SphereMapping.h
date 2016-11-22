/************************************************************
"GL_LINE_STRIP"などの説明
	http://openframeworks.cc/documentation/gl/ofVbo/
	
	
	http://openframeworks.cc/documentation/gl/ofShader/#show_setGeometryOutputType
	
ofShader
	http://openframeworks.cc/documentation/gl/ofShader/
	
	description
		setGeometryInputType(...), setGeometryOutputType(...)
		では、指定可能なtypeに制限がある。
		
Geometry shader input/output 指定
	http://miffysora.wikidot.com/geometry-shader
	
	description
		input
			GL_POINTS					1
			GL_LINES					2
			GL_LINES_ADJACENCY_EXT		4
			GL_TRIANGLES				3
			GL_TRIANGLES_ADJACENCY_EXT	6
			
		output
			GL_POINTS
			GL_LINE_STRIP
			GL_TRIANGLE_STRIP
			
		入力がGL_POINTSで出力がGL_TRIANGLE_STRIPなんていうのもあり。
		入力は、単に１入力プリミティブあたりに何個の頂点を送るか、だけと考えて良い。
		
Vbo.draw(int drawMode, int first, int total);
	http://openframeworks.cc/documentation/gl/ofVbo/#show_draw
	drawModeは、
		GL_POINTS
		GL_LINE_STRIP
		GL_LINE_LOOP
		GL_LINES
		GL_TRIANGLE_STRIP
		GL_TRIANGLE_FAN
		GL_TRIANGLES
		GL_QUAD_STRIP
		GL_QUADS
		GL_POLYGON 
	のみacceptableと記述があるが、shaderを使用する際は、setGeometryInputType()で指定したtype(例えば GL_LINES_ADJACENCY_EXT)を引数とする.
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class MOV_EFFECT__SPHERE_MAPPING{
private:
	/****************************************
	****************************************/
	enum{
		// NUM_QUADS = 1500,
		NUM_QUADS = 1200,
		NUM_VERTS = NUM_QUADS * 4,
	};
	
	/****************************************
	****************************************/
	ofVbo Vbo;
	ofVec3f Verts[NUM_VERTS];
	ofFloatColor Color[NUM_VERTS];

	ofShader shader;	//Shader
	
	float LastINT;
	float phase;

public:
	/****************************************
	****************************************/
	MOV_EFFECT__SPHERE_MAPPING();
	
	void setup();
	void update();
	void draw(ofFbo* fbo_src, ofFbo* fbo_dst);

};