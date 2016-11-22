/************************************************************
************************************************************/
#include "movEffect_SphereMapping.h"

/************************************************************
************************************************************/

/******************************
******************************/
MOV_EFFECT__SPHERE_MAPPING::MOV_EFFECT__SPHERE_MAPPING()
: LastINT(0)
, phase(0)
{
}

/******************************
******************************/
void MOV_EFFECT__SPHERE_MAPPING::setup()
{
	/********************
	1st, make a triangle.
	Then extend it to parallelogram.
	********************/
	float Rad = 250;	//The sphere's radius
	// float rad = 25;		//Maximal triangle's “radius”
	float rad = 28;		//Maximal triangle's “radius”

	for (int i=0; i<NUM_QUADS; i++) {
		ofVec3f center( ofRandom( -1, 1 ), ofRandom( -1, 1 ), ofRandom( -1, 1 ) );
		center.normalize();
		center *= Rad;

		for (int j=0; j<3; j++) {
			Verts[ i*4 + j ].set(center + ofVec3f( ofRandom( -rad, rad ), ofRandom( -rad, rad ), ofRandom( -rad, rad ) ) );
		}
		Verts[i * 4 + 3].set(Verts[i * 4 + 0] + (Verts[i * 4 + 1] - Verts[i * 4 + 0]) + (Verts[i * 4 + 2] - Verts[i * 4 + 0])); // parallelogram.
		// Verts[i * 4 + 3] = Verts[i * 4 + 2];
	}
	for (int i=0; i<NUM_VERTS; i++)	Color[i].set(1.0, 1.0, 1.0, 1.0);
	
	Vbo.setVertexData(Verts, NUM_VERTS, GL_DYNAMIC_DRAW);
	Vbo.setColorData(Color, NUM_VERTS, GL_DYNAMIC_DRAW);

	
	/********************
	setGeometryInputType(), setGeometryOutputType()に指定可能なtypeは決まっている。
		http://openframeworks.cc/documentation/gl/ofShader/#show_setGeometryOutputType
		
	入力は、単に１入力プリミティブあたりに何個の頂点を送るか、だけと考えて良い。
		http://miffysora.wikidot.com/geometry-shader
		
	並べた順にshaderに渡される。
	
	outputは、「typeと順番」で描画内容が変わってくるので注意してoutputする。
	inputの時に、混乱なきよう、順序を考慮しておくのが良い。
		http://openframeworks.cc/documentation/gl/ofVbo/
	********************/
	//We must to specify geometry shader parameters before loading shader
	shader.setGeometryInputType( GL_LINES_ADJACENCY_EXT );
	shader.setGeometryOutputType( GL_TRIANGLE_STRIP );
	
	/********************
	ofVboでは、vbo.draw();で一気に描画コマンドを投げるが、shaderでは、setGeometryInputType()で指定した単位でgeometryが渡される。
	geometryが渡される度、geometry shaderが走る。
	shader:mainにて、EndPrimitiveにより、その回で出力するoutput geometryを終了。
	この、「その回で出力するgeometry」にてoutputするverticesをここで指定。
	********************/
	shader.setGeometryOutputCount( 4 );	//Maximal possible number of output vertices
	
	//Load shader
	shader.load( "movEffect/SphereMapping/SphereMapping.vert", "movEffect/SphereMapping/SphereMapping.frag", "movEffect/SphereMapping/SphereMapping.geom");
}

/******************************
******************************/
void MOV_EFFECT__SPHERE_MAPPING::update()
{
	float time = ofGetElapsedTimef();
	float dt = ofClamp( time - LastINT, 0, 0.1 );
	LastINT = time;
	
	float speed = 2;
	phase += speed * dt;
}

/******************************
******************************/
void MOV_EFFECT__SPHERE_MAPPING::draw(ofFbo* fbo_src, ofFbo* fbo_dst)
{
	ofPushStyle();
	
	/********************
	********************/
	// glDisable(GL_CULL_FACE);
	ofEnableDepthTest();
	ofFill();
	
	/********************
	draw to local fbo that has same size of fbo_src.
	********************/
	ofFbo fbo_dst_local;
	fbo_dst_local.allocate(fbo_src->getWidth(), fbo_src->getHeight(), GL_RGB);
	
	fbo_dst_local.begin();
		ofBackground(0, 0, 0, 0);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		// ofEnableBlendMode(OF_BLENDMODE_ALPHA);
			
		ofSetColor(255, 255, 255, 90);
		fbo_src->draw(0, 0, fbo_dst_local.getWidth(), fbo_dst_local.getHeight());
		
		ofSetColor(255, 255, 255, 255);
		
		ofPushMatrix();
		
		ofTranslate( fbo_src->getWidth()/2, fbo_src->getHeight()/2, 0 );
		float time = ofGetElapsedTimef();
		float angle = time * 15; // deg.
		ofRotate( angle, 0, 1, 0 );
		
		shader.begin();
			shader.setUniform1f( "phase", phase );
			shader.setUniform1f( "TextureSize_w", fbo_src->getWidth() );
			shader.setUniform1f( "TextureSize_h", fbo_src->getHeight() );
			shader.setUniformTexture( "texture1", fbo_src->getTextureReference(), 1 );
			
			Vbo.draw(GL_LINES_ADJACENCY_EXT, 0, NUM_VERTS);
		shader.end();
	
		ofPopMatrix();
	fbo_dst_local.end();
	
	/********************
	表面のみを描く:戻す
	********************/
	// glEnable(GL_CULL_FACE); 
	// glCullFace(GL_BACK);
	
	ofDisableDepthTest();
	
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
	
	
	ofPopStyle();
}


