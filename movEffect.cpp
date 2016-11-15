/************************************************************
************************************************************/
#include "movEffect.h"

/************************************************************
************************************************************/
/********************
********************/
int MOV_EFFECT::EffectTypeCombination_id = 0;

/********************
********************/
struct WEIGHT_GRAY{
	int weight;
	bool b_Gray;
};

WEIGHT_GRAY EffectCombination[MOV_EFFECT::NUM_EFFECT_TYPE_COMBINATION] = {
//			→ mov								
//	↓ mov 0		EFFECT_TYPE__KALEIDOSCOPE	EFFECT_TYPE__SPHERE_TEXTURE	EFFECT_TYPE__BOX_TEXTURE	EFFECT_TYPE__CYLINDER_TEXTURE	EFFECT_TYPE__CONE_TEXTURE	EFFECT_TYPE__SPLIT_2x2	EFFECT_TYPE__SPLIT_3x3	EFFECT_TYPE__SPLIT_5x5	EFFECT_TYPE__PARTICLE
/*	EFFECT_TYPE__KALEIDOSCOPE	*/	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__SPHERE_TEXTURE	*/	{1, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__BOX_TEXTURE	*/	{1, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__CYLINDER_TEXTURE	*/	{1, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__CONE_TEXTURE	*/	{1, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__SPLIT_2x2	*/	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__SPLIT_3x3	*/	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__SPLIT_5x5	*/	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1,false},
/*	EFFECT_TYPE__PARTICLE	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},
};

/************************************************************
************************************************************/

/******************************
******************************/
MOV_EFFECT::MOV_EFFECT()
: EffectType(EFFECT_TYPE__KALEIDOSCOPE)
, b_cam_orbit(false)
{
}

/******************************
******************************/
MOV_EFFECT::~MOV_EFFECT()
{
}

/******************************
******************************/
bool MOV_EFFECT::IsGray()
{
	return EffectCombination[EffectTypeCombination_id].b_Gray;
}

/******************************
******************************/
void MOV_EFFECT::RandomSet_EffectType_Combination(MOV_EFFECT& mov, MOV_EFFECT& mov_0)
{
	int Weight[NUM_EFFECT_TYPE_COMBINATION];
	for(int i = 0; i < NUM_EFFECT_TYPE_COMBINATION; i++){
		Weight[i] = EffectCombination[i].weight;
	}
	
	EffectTypeCombination_id = Dice_index(Weight, NUM_EFFECT_TYPE_COMBINATION);
	
	mov.Set_EffectType(EFFECT_TYPE(EffectTypeCombination_id / int(NUM_EFFECT_TYPE)));
	mov_0.Set_EffectType(EFFECT_TYPE(EffectTypeCombination_id % int(NUM_EFFECT_TYPE)));
	
	printf("mov   type = %d.\n", mov.EffectType);
	printf("mov_0 type = %d.\n", mov_0.EffectType);
}

/******************************
******************************/
void MOV_EFFECT::Set_EffectType(int id)
{
	/********************
	********************/
	if( (id < 0) || (NUM_EFFECT_TYPE <= id) ){
		printf("no such Effect type\n");
		return;
	}
	
	/********************
	********************/
	EffectType = EFFECT_TYPE(id);
	
	switch(EffectType){
		case EFFECT_TYPE__SPHERE_TEXTURE:
		case EFFECT_TYPE__BOX_TEXTURE:
		case EFFECT_TYPE__CYLINDER_TEXTURE:
		case EFFECT_TYPE__CONE_TEXTURE:
		case EFFECT_TYPE__PARTICLE:
			b_cam_orbit = true;
			break;
			
		case EFFECT_TYPE__KALEIDOSCOPE:
		case EFFECT_TYPE__SPLIT_2x2:
		case EFFECT_TYPE__SPLIT_3x3:
		case EFFECT_TYPE__SPLIT_5x5:
			cam.reset();
			cam.setDistance(ofGetWidth() * 0.4);
			b_cam_orbit = false;
			break;
			
		default:
			cam.reset();
			cam.setDistance(ofGetWidth() * 0.4);
			b_cam_orbit = false;
			break;
	}
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
	
	cylinder.set(230, 400); // cylinder.set( cylinderRadius, cylinderHeight );
	cylinder.setResolution(80, 80, 10); // void ofCylinderPrimitive::setResolution(int radiusSegments, int heightSegments, int capSegments=2)
	cylinder.rotate(180, 0, 1, 0);
	
	cone.set(250, 400, 60, 60); // cone.set( coneRadius, coneHeight, coneRadiusSegments, coneHeightSegments )
	cone.rotate(180, 0, 1, 0);
	
	/********************
	********************/
	for(int i = 0; i < PARTICLE_WIDTH; i++){
		for(int j = 0; j < PARTICLE_HEIGHT; j++){
			Verts[j * PARTICLE_WIDTH + i].set(i - PARTICLE_WIDTH/2, j - PARTICLE_HEIGHT/2, 0);
			Color[j * PARTICLE_WIDTH + i].set(1.0, 1.0, 1.0, 1.0);
		}
	}
	
	Vbo.setVertexData(Verts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	Vbo.setColorData(Color, NUM_PARTICLES, GL_DYNAMIC_DRAW);
}

/******************************
******************************/
void MOV_EFFECT::update()
{
    sphere.set(ofGetWidth() * 0.17, 80);
	Box.set(ofGetWidth() * 0.18);
	cylinder.set(ofGetWidth() * 0.14, ofGetWidth() * 0.25);
	cone.set(ofGetWidth() * 0.15, ofGetWidth() * 0.25, 60, 60);
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
			case EFFECT_TYPE__BOX_TEXTURE:
			case EFFECT_TYPE__CYLINDER_TEXTURE:
			case EFFECT_TYPE__CONE_TEXTURE:
				draw_PrimitiveTexture(fbo_src, fbo_dst, EffectType);
				break;
				
			case EFFECT_TYPE__SPLIT_2x2:
				draw_Split(fbo_src, fbo_dst, 2, true);
				break;
				
			case EFFECT_TYPE__SPLIT_3x3:
				draw_Split(fbo_src, fbo_dst, 3, true);
				break;
				
			case EFFECT_TYPE__SPLIT_5x5:
				draw_Split(fbo_src, fbo_dst, 5, true);
				break;
				
			case EFFECT_TYPE__PARTICLE:
				draw_Particle(fbo_src, fbo_dst);
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
void MOV_EFFECT::draw_Particle(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(PARTICLE_WIDTH, PARTICLE_HEIGHT, GL_RGBA);
	
	fbo_dst_local.begin();
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	fbo_dst_local.end();
	
	/********************
	********************/
	/* */
	if(fbo_dst){
		fbo_dst->begin();
		
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
	}else{
		ofEnableAlphaBlending();
	}
	
	/* */
	ofFloatPixels pixels;
	fbo_dst_local.readToPixels(pixels);
	
	for(int x = 0; x < pixels.getWidth(); x++){
		for(int y = 0; y < pixels.getHeight(); y++){
			ofColor color = pixels.getColor(x, y);
			
			float r = float(color.r) / 255;
			float g = float(color.g) / 255;
			float b = float(color.b) / 255;
			
			float brightness = (r + g + b) / 3.0f;
			
			Verts[y * PARTICLE_WIDTH + x] = ofVec3f(x - PARTICLE_WIDTH/2, y - PARTICLE_HEIGHT/2, brightness * 255 - 128);
			Color[y * PARTICLE_WIDTH + x] = ofFloatColor(r, g, b, 0.8);
		}
	}
	
	Vbo.updateVertexData(Verts, NUM_PARTICLES);
	Vbo.updateColorData(Color, NUM_PARTICLES);
	
	/* */
	cam_orbit_motion();
	
	cam.begin();
	ofPushMatrix();
	ofScale(1, -1, 1);
	glPointSize(1.0);
	Vbo.draw(GL_POINTS, 0, NUM_PARTICLES);
	ofPopMatrix();
	cam.end();
	
	/* */
	if(fbo_dst) fbo_dst->end();
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
		ofDisableAlphaBlending();
		
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
		ofDisableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
		
	}else{
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		fbo_dst_local.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

/******************************
******************************/
void MOV_EFFECT::cam_orbit_motion()
{
	if(b_cam_orbit){
		float time = ofGetElapsedTimef();
		float longitude = 15 * time; // rotation speed
		float latitude = ofGetWidth() * 0.015 * sin(time*0.8); // y方向に軽く揺らす.
		float radius = ofGetWidth() * 0.4 + ofGetWidth() * 0.04 * sin(time*0.4);
		cam.orbit( longitude, latitude, radius, ofPoint(0,0,0) );
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
			// sphere.mapTexCoords(0, fbo_src->getHeight(), fbo_src->getWidth(), 0);
			sphere.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
		case EFFECT_TYPE__BOX_TEXTURE:
			// Box.mapTexCoords(0, fbo_src->getHeight(), fbo_src->getWidth(), 0);
			Box.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
			
		case EFFECT_TYPE__CYLINDER_TEXTURE:
			// cylinder.mapTexCoords(0, fbo_src->getHeight(), fbo_src->getWidth(), 0);
			cylinder.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
			
		case EFFECT_TYPE__CONE_TEXTURE:
			// cone.mapTexCoords(0, fbo_src->getHeight(), fbo_src->getWidth(), 0);
			cone.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
	}
	
	ofEnableDepthTest();
	fbo_dst_local.begin();
		fbo_src->getTextureReference().bind();
		
		cam_orbit_motion();
		
		cam.begin();
			ofPushMatrix();
			ofScale(1, -1);
			
			/*
			// comment out light so that the face get brighter.
			// light.setPosition(ofGetWidth()/2, ofGetHeight()/2, 600);
			// light.setPosition(fbo_dst_local.getWidth()/4, fbo_dst_local.getHeight()/4, 600);
			// light.enable();
			*/
			material.begin();
			
			ofBackground(0, 0, 0, 0);
			ofSetColor(255, 255, 255, 255);
			ofDisableAlphaBlending();
			
			switch(EffectType){
				case EFFECT_TYPE__SPHERE_TEXTURE:
					sphere.draw();
					break;
				case EFFECT_TYPE__BOX_TEXTURE:
					Box.draw();
					break;
				case EFFECT_TYPE__CYLINDER_TEXTURE:
					cylinder.draw();
					break;
					
				case EFFECT_TYPE__CONE_TEXTURE:
					cone.draw();
					break;
			}
			
			ofPopMatrix();
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
		ofDisableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
		
	}else{
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
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
		ofDisableAlphaBlending();
		
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
		ofDisableAlphaBlending();
		
		fbo_dst_local.draw(0, 0, fbo_dst->getWidth(), fbo_dst->getHeight());
		fbo_dst->end();
		
	}else{
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
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
		ofDisableAlphaBlending();
		
		fbo_src->draw(0, 0);
		
		fbo_dst->end();
	}else{
		ofSetColor(255, 255, 255, 255);
		ofEnableAlphaBlending();
		
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
		case '8':
		{
			Set_EffectType(key - '0');
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

