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
//	↓ mov 0		KALEIDOSCOPE	SPHERE_TEXTURE	BOX_TEXTURE	CYLINDER_TEXTURE	CONE_TEXTURE	BOXES_MATRIX_TEXTURE	SPHERES_MATRIX_TEXTURE	CYLINDERS_MATRIX_TEXTURE	SPLIT_2x2	SPLIT_3x3	SPLIT_5x5	PARTICLE	MOSAIC	NOISE	SPHERE_MAPPING	MIRROR_LR	MIRROR_VERT	LINE_OFFSET_PERLINE
/*	EFFECT_TYPE__KALEIDOSCOPE	*/	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1,false},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__SPHERE_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__BOX_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__CYLINDER_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__CONE_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__BOXES_MATRIX_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__SPHERES_MATRIX_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE	*/	{1,false},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{0, true},	{1, true},	{1, true},	{1, true},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__SPLIT_2x2	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1, true},	{1, true},	{1, true},	{1,false},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__SPLIT_3x3	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1, true},	{1, true},	{1,false},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__SPLIT_5x5	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1, true},	{1,false},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__PARTICLE	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},	{0, true},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},
/*	EFFECT_TYPE__MOSAIC	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__NOISE	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__SPHERE_MAPPING	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},	{1, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__MIRROR_LR	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},	{1, true},	{1, true},
/*	EFFECT_TYPE__MIRROR_VERT	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},	{1, true},
/*	EFFECT_TYPE__LINE_OFFSET_PERLINE	*/	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{1,false},	{0, true},
};

/************************************************************
************************************************************/

/******************************
******************************/
MOV_EFFECT::MOV_EFFECT()
: EffectType(EFFECT_TYPE__KALEIDOSCOPE)
, b_cam_orbit(false)
, b_cam_Enable_MouseInput(true)
, k_angle(0)
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
		case EFFECT_TYPE__BOXES_MATRIX_TEXTURE:
		case EFFECT_TYPE__SPHERES_MATRIX_TEXTURE:
		case EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE:
			b_cam_orbit = true;
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
	shader_Mosaic.load( "movEffect/mosaic/Mosaic.vert", "movEffect/mosaic/Mosaic.frag");
	shader_Noise.load( "movEffect/Noise/Noise.vert", "movEffect/Noise/Noise.frag");
	shader_Mirror_LR.load( "movEffect/Mirror_LR/Mirror_LR.vert", "movEffect/Mirror_LR/Mirror_LR.frag");
	shader_Mirror_Vert.load( "movEffect/Mirror_Vertical/Mirror_Vertical.vert", "movEffect/Mirror_Vertical/Mirror_Vertical.frag");

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
	
	/********************
	********************/
	SphereMapping.setup();
	LineOffset_Perlin.setup();
}

/******************************
******************************/
void MOV_EFFECT::update()
{
	/********************
	********************/
	switch(EffectType){
		case EFFECT_TYPE__SPHERE_TEXTURE:
			sphere.set(ofGetWidth() * 0.17, 80);
			break;
			
		case EFFECT_TYPE__SPHERES_MATRIX_TEXTURE:
			sphere.set(ofGetWidth() * 0.06, 80);
			break;
			
		case EFFECT_TYPE__BOX_TEXTURE:
			Box.set(ofGetWidth() * 0.18);
			break;
			
		case EFFECT_TYPE__BOXES_MATRIX_TEXTURE:
			Box.set(ofGetWidth() * 0.15);
			break;
			
		case EFFECT_TYPE__CYLINDER_TEXTURE:
			cylinder.set(ofGetWidth() * 0.14, ofGetWidth() * 0.25);
			break;
			
		case EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE:
		{
			float sizeDown = 0.4;
			cylinder.set(ofGetWidth() * 0.14 * sizeDown, ofGetWidth() * 0.25 * sizeDown);
		}
			break;
			
		case EFFECT_TYPE__CONE_TEXTURE:
			cone.set(ofGetWidth() * 0.15, ofGetWidth() * 0.25, 60, 60);
			break;
			
		default:
			break;
	}
	
	/********************
	********************/
	SphereMapping.update();
	LineOffset_Perlin.update();
}

/******************************
description
param
	fbo_dst
		NULL : draw to screen.
******************************/
void MOV_EFFECT::draw(bool b_EffectOn, ofFbo* fbo_src, ofFbo* fbo_dst)
{
	ofPushStyle();
	
	if(b_EffectOn){
		switch(EffectType){
			case EFFECT_TYPE__KALEIDOSCOPE:
				draw_Kaleido(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__SPHERE_TEXTURE:
			case EFFECT_TYPE__BOX_TEXTURE:
			case EFFECT_TYPE__CYLINDER_TEXTURE:
			case EFFECT_TYPE__CONE_TEXTURE:
			case EFFECT_TYPE__BOXES_MATRIX_TEXTURE:
			case EFFECT_TYPE__SPHERES_MATRIX_TEXTURE:
			case EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE:
				draw_PrimitiveTexture(fbo_src, fbo_dst, EffectType);
				break;
				
			case EFFECT_TYPE__SPLIT_2x2:
				draw_Split(fbo_src, fbo_dst, 2);
				break;
				
			case EFFECT_TYPE__SPLIT_3x3:
				draw_Split(fbo_src, fbo_dst, 3);
				break;
				
			case EFFECT_TYPE__SPLIT_5x5:
				draw_Split(fbo_src, fbo_dst, 5);
				break;
				
			case EFFECT_TYPE__PARTICLE:
				draw_Particle(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__MOSAIC:
				draw_Mosaic(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__NOISE:
				draw_Noise(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__SPHERE_MAPPING:
				SphereMapping.draw(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__MIRROR_LR:
				draw_Mirror_LR(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__MIRROR_VERT:
				draw_Mirror_Vert(fbo_src, fbo_dst);
				break;
				
			case EFFECT_TYPE__LINE_OFFSET_PERLINE:
				LineOffset_Perlin.draw(fbo_src, fbo_dst);
				break;
				
			default:
				draw_EffectNone(fbo_src, fbo_dst);
				break;
		}
		
	}else{
		draw_EffectNone(fbo_src, fbo_dst);
	}
	
	ofPopStyle();
}

/******************************
******************************/
void MOV_EFFECT::draw_Mirror_Vert(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
	shader_Mirror_Vert.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		shader_Mirror_Vert.setUniform2f( "screenCenter", fbo_dst_local.getWidth()/2, fbo_dst_local.getHeight()/2 );
		
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader_Mirror_Vert.end();
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
void MOV_EFFECT::draw_Mirror_LR(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
	shader_Mirror_LR.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		shader_Mirror_LR.setUniform2f( "screenCenter", fbo_dst_local.getWidth()/2, fbo_dst_local.getHeight()/2 );
		
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader_Mirror_LR.end();
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
void MOV_EFFECT::draw_Noise(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
	shader_Noise.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		shader_Noise.setUniform1f("Time", ofGetElapsedTimef());
		
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader_Noise.end();
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
void MOV_EFFECT::draw_Mosaic(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
	shader_Mosaic.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		shader_Mosaic.setUniform1i("MosaicSize", int(ofGetWidth() * 0.02));
		shader_Mosaic.setUniform1f("now_sec", ofGetElapsedTimef());
		
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
	
	shader_Mosaic.end();
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
void MOV_EFFECT::draw_Particle(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	draw to fbo : particle image size
	********************/
	ofFbo fbo_particleImageSize;
	fbo_particleImageSize.allocate(PARTICLE_WIDTH, PARTICLE_HEIGHT, GL_RGB);
	
	fbo_particleImageSize.begin();
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		fbo_src->draw(0, 0, fbo_particleImageSize.getWidth(), fbo_particleImageSize.getHeight());
	
	fbo_particleImageSize.end();
	
	/********************
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
		/********************
		********************/
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		
		ofEnableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		
		/********************
		********************/
		ofFloatPixels pixels;
		fbo_particleImageSize.readToPixels(pixels);
		
		for(int x = 0; x < pixels.getWidth(); x++){
			for(int y = 0; y < pixels.getHeight(); y++){
				ofColor color = pixels.getColor(x, y);
				
				float r = float(color.r) / 255;
				float g = float(color.g) / 255;
				float b = float(color.b) / 255;
				
				float brightness = (r + g + b) / 3.0f;
				
				// Verts[y * PARTICLE_WIDTH + x] = ofVec3f(x - PARTICLE_WIDTH/2, y - PARTICLE_HEIGHT/2, brightness * 90 - 45); // Particle:small
				Verts[y * PARTICLE_WIDTH + x] = ofVec3f(x - PARTICLE_WIDTH/2, y - PARTICLE_HEIGHT/2, brightness * 160 - 80); // Particle:middle
				// Verts[y * PARTICLE_WIDTH + x] = ofVec3f(x - PARTICLE_WIDTH/2, y - PARTICLE_HEIGHT/2, brightness * 255 - 128); // Particle:large
				
				Color[y * PARTICLE_WIDTH + x] = ofFloatColor(r, g, b, 0.8);
			}
		}
		
		Vbo.updateVertexData(Verts, NUM_PARTICLES);
		Vbo.updateColorData(Color, NUM_PARTICLES);
		
		/********************
		********************/
		cam_orbit_motion();
		
		cam.begin();
		ofPushMatrix();
		ofScale(1, -1, 1);
		
		// glPointSize(2.5); // Particle:small
		glPointSize(2.0); // Particle:middle
		
		Vbo.draw(GL_POINTS, 0, NUM_PARTICLES);
		ofPopMatrix();
		cam.end();
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
void MOV_EFFECT::draw_Split(ofFbo* fbo_src, ofFbo* fbo_dst, int NumSplit)
{
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
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
	if(EffectType == EFFECT_TYPE__PARTICLE){
		if(b_cam_orbit){
			float time = ofGetElapsedTimef();
			float longitude = 15 * time; // rotation speed
			// float latitude = ofGetWidth() * 0.013 * sin(time*0.8); // y方向に軽く揺らす.
			float latitude = 15 * sin(time*0.8); // y方向に軽く揺らす.
			
			// float radius = ofGetWidth() * 0.08 + ofGetWidth() * 0.008 * sin(time*0.4); // Particle:small
			float radius = ofGetWidth() * 0.2 + ofGetWidth() * 0.02 * sin(time*0.4); // Particle:middle
			
			cam.orbit( longitude, latitude, radius, ofPoint(0,0,0) );
		}
		
	}else{
		if(b_cam_orbit){
			float time = ofGetElapsedTimef();
			float longitude = 15 * time; // rotation speed
			// float latitude = ofGetWidth() * 0.013 * sin(time*0.8); // y方向に軽く揺らす.
			float latitude = 15 * sin(time*0.8); // y方向に軽く揺らす.
			float radius = ofGetWidth() * 0.4 + ofGetWidth() * 0.04 * sin(time*0.4);
			cam.orbit( longitude, latitude, radius, ofPoint(0,0,0) );
		}
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
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	switch(EffectType){
		case EFFECT_TYPE__SPHERE_TEXTURE:
		case EFFECT_TYPE__SPHERES_MATRIX_TEXTURE:
			sphere.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
			
		case EFFECT_TYPE__BOX_TEXTURE:
		case EFFECT_TYPE__BOXES_MATRIX_TEXTURE:
			Box.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
			
		case EFFECT_TYPE__CYLINDER_TEXTURE:
		case EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE:
			cylinder.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
			
		case EFFECT_TYPE__CONE_TEXTURE:
			cone.mapTexCoords(0, 0, fbo_src->getWidth(), fbo_src->getHeight());
			break;
			
		default:
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
					sphere.setPosition(0, 0, 0);
					sphere.draw();
					break;
					
				case EFFECT_TYPE__BOX_TEXTURE:
					Box.setPosition(0, 0, 0);
					Box.draw();
					break;
					
				case EFFECT_TYPE__CYLINDER_TEXTURE:
					cylinder.setPosition(0, 0, 0);
					cylinder.draw();
					break;
					
				case EFFECT_TYPE__CONE_TEXTURE:
					cone.setPosition(0, 0, 0);
					cone.draw();
					break;
					
				case EFFECT_TYPE__BOXES_MATRIX_TEXTURE:
					draw_BoxMatrix();
					break;
					
				case EFFECT_TYPE__SPHERES_MATRIX_TEXTURE:
					draw_SphereMatrix();
					break;
					
				case EFFECT_TYPE__CYLINDERS_MATRIX_TEXTURE:
					draw_CylinderMatrix();
					break;
					
				default:
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
void MOV_EFFECT::draw_CylinderMatrix()
{
	const int NUM_PRIMITIVES = 9;
	float offset = 2;
	float angle = 5;
	ofVec3f axis = ofVec3f(0, 1, 0);
	
	ofVec3f PosMatrix[NUM_PRIMITIVES] =	{
											ofVec3f(-2, -1, -1),
											ofVec3f(-1, -1,  1),
											ofVec3f( 1, -1,  0),
											
											ofVec3f(-1,  0,  0),
											ofVec3f( 0,  0, -2),
											ofVec3f( 1,  0,  1),
											
											ofVec3f(-2,  1,  0),
											ofVec3f( 1,  1, -1),
											ofVec3f( 2,  1,  1),
										};
	
	/********************
	camera座標が動く.
	********************/
	for(int i = 0; i < NUM_PRIMITIVES; i++){
		ofPushMatrix();
		
		ofTranslate(PosMatrix[i].x * cylinder.getRadius() * offset, PosMatrix[i].y * cylinder.getHeight(), PosMatrix[i].z * cylinder.getRadius() * offset);
		ofRotate(angle * i, axis.x, axis.y, axis.z);
		
		cylinder.draw();
		ofPopMatrix();
	}
}

/******************************
******************************/
void MOV_EFFECT::draw_SphereMatrix()
{
	const int NUM_PRIMITIVES = 9;
	float offset = 1.9;
	float angle = 20;
	ofVec3f axis = ofVec3f(0, 1, 0);
	
	ofVec3f PosMatrix[NUM_PRIMITIVES] =	{
											ofVec3f(-2, -1, -1),
											ofVec3f(-1, -1,  1),
											ofVec3f( 1, -1,  0),
											
											ofVec3f(-1,  0,  0),
											ofVec3f( 0,  0, -2),
											ofVec3f( 1,  0,  1),
											
											ofVec3f(-2,  1,  0),
											ofVec3f( 1,  1, -1),
											ofVec3f( 2,  1,  1),
										};
	
	/********************
	camera座標が動く.
	********************/
	for(int i = 0; i < NUM_PRIMITIVES; i++){
		ofPushMatrix();
		
		ofTranslate(PosMatrix[i].x * sphere.getRadius() * offset, PosMatrix[i].y * sphere.getRadius() * offset, PosMatrix[i].z * sphere.getRadius() * offset);
		ofRotate(angle * i, axis.x, axis.y, axis.z);
		
		sphere.draw();
		ofPopMatrix();
	}
}

/******************************
******************************/
void MOV_EFFECT::draw_BoxMatrix()
{
	const int NUM_PRIMITIVES = 9;
	
	ofVec3f PosMatrix[NUM_PRIMITIVES] =	{
											ofVec3f(-2, -1, -1),
											ofVec3f(-1, -1,  1),
											ofVec3f( 1, -1,  0),
											
											ofVec3f(-1,  0,  0),
											ofVec3f( 0,  0, -2),
											ofVec3f( 1,  0,  1),
											
											ofVec3f(-2,  1,  0),
											ofVec3f( 1,  1, -1),
											ofVec3f( 2,  1,  1),
										};
	
	/********************
	camera座標が動く.
	********************/
	for(int i = 0; i < NUM_PRIMITIVES; i++){
		ofPushMatrix();
		
		ofTranslate(PosMatrix[i].x * Box.getWidth(), PosMatrix[i].y * Box.getHeight(), PosMatrix[i].z * Box.getDepth());
		
		Box.draw();
		ofPopMatrix();
	}
}

/******************************
******************************/
void MOV_EFFECT::draw_Kaleido(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	/********************
	********************/
	static float LastInt_sec = 0;
	float now = ofGetElapsedTimef();
	float dt = ofClamp(now - LastInt_sec, 0, 0.1);
	
	const float deg_per_sec = 10;
	k_angle += deg_per_sec * dt;
	if(360 <= k_angle) k_angle -= 360;
	
	LastInt_sec = now;
	
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
	shader_Kaleido.begin();
	
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		shader_Kaleido.setUniform2f( "screenCenter", fbo_dst_local.getWidth()/2, fbo_dst_local.getHeight()/2 );
		shader_Kaleido.setUniform2f( "kcenter", fbo_src->getWidth()/2, fbo_src->getHeight()/2 );
		shader_Kaleido.setUniform1i( "ksectors", 10 );
		
		shader_Kaleido.setUniform1f( "kangleRad", ofDegToRad(k_angle) );
		// shader_Kaleido.setUniform1f( "kangleRad", 0 );
		
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
		case '9':
		{
			if(key - '0' < NUM_EFFECT_TYPE){
				Set_EffectType(key - '0');
			}
		}
			break;
			
		case 'c':
			b_cam_Enable_MouseInput = !b_cam_Enable_MouseInput;
			if(b_cam_Enable_MouseInput)	cam.enableMouseInput();
			else						cam.disableMouseInput();
			
			printf("b_cam_Enable_MouseInput = %d\n", b_cam_Enable_MouseInput);

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

