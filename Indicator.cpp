/************************************************************
************************************************************/
#include "Indicator.h"


/************************************************************
************************************************************/

/******************************
******************************/
INDICATOR::INDICATOR()
{
}

/******************************
******************************/
INDICATOR::~INDICATOR()
{
}

/******************************
******************************/
void INDICATOR::exit() {
	// gui.saveToFile( "settings_exit.xml" );
}

/******************************
******************************/
void INDICATOR::setup(){
	/********************
	********************/
	gui.setup( "Indicator", "settings.xml" );
	
	gui.add( LineWidth.setup( "LineWidth", 1, 1, 10 ) );
	
	if(BootMode == MODE_TEST){
		gui.add(MusicSync.setup("MusicSync", false));
		gui.add(b_SelfRotation.setup("Self Rotaion", false));
	}else{ // Demo mode
		gui.add(MusicSync.setup("MusicSync", true));
		gui.add(b_SelfRotation.setup("Self Rotaion", true));
	}
	
	gui.add( countX.setup( "countX", 0, 0, 200 ) );
	gui.add( stepX.setup( "stepX", 200, 0, 300 ) );
	gui.add( twistX.setup( "twistX", 0, -45, 45 ) );
	
	gui.add( countY.setup( "countY", 0, 0, 100) );
	gui.add( stepY.setup( "stepY", 20, 0, 300 ) );
	gui.add( twistY.setup( "twistY", 0, -30, 30 ) );
	gui.add( pinchY.setup( "pinchY", 0, 0, 1 ) );
	
	globalGroup.setup( "Global" );
	globalGroup.add( g_Scale.setup( "g_Scale", 0.7, 0.0, 1 ) );
	globalGroup.add( g_Rotate.setup( "g_Rotate", 0, -180, 180 ) );
	gui.add( &globalGroup );
	
	/* */
	primGroup.setup( "Primitive" );
	primGroup.add( primitive_shiftY.setup( "shiftY", 0.0, -1000.0, 1000.0 ) );
	primGroup.add( primitive_rotate.setup( "rotate", 0.0, -180.0, 180.0 ) );
	
	primGroup.add( b_PrimitiveSize_by_x.setup( "size by x", true ) );
	primGroup.add( primitive_size.setup(	"size",
											ofVec2f(6,6),
											ofVec2f(0,0),
											ofVec2f(20,20) ) );
	
	primGroup.add( color.setup(	"color",
								ofColor(50, 50, 255, 255),
								ofColor(0,0,0,0),
								ofColor::white ) );
	primGroup.add( filled.setup( "filled", false ) );
	primGroup.add( type.setup( "type", false ) );
	gui.add( &primGroup );


	showGui = false;
	
	/********************
	********************/
	ofVec3f point0(0, 0);
	for(int i = 0; i < NUM_VERTS; i++){
		vbo_Verts[i].set(point0);
		vbo_Color[i].set(1.0, 0.0, 0.0, 1.0);
	}
	
	Vbo.setVertexData(vbo_Verts, NUM_VERTS, GL_DYNAMIC_DRAW);
	Vbo.setColorData(vbo_Color, NUM_VERTS, GL_DYNAMIC_DRAW);
	
	/********************
	********************/
	if(BootMode == MODE_DEMO)	RandomSet_Pattern();
	else						id_pattern = -1;
}

/******************************
******************************/
void INDICATOR::update(vector<float>& spectrum)
{
	if( (spectrum.size() != 0) && MusicSync )	changeParam_MusicSync(spectrum);
	if(b_SelfRotation)							SelfRotaion();
}

/******************************
******************************/
void INDICATOR::changeParam_MusicSync(vector<float>& spectrum)
{
	float Lev = spectrum[1];
	
	switch(id_pattern){
		case -1:
			countX = ofMap(Lev, 0, 2.0, 0, 200, true);
			break;
			
		case 0:
		case 1:
			stepX = ofMap(Lev, 0, 2.0, 50, 200, true);
			break;
			
		case 2:
		{
			stepX = ofMap(Lev, 0, 2.0, 50, 200, true);
		}
			break;
			
		case 3:
		case 4:
		{
			twistX = ofMap(Lev, 0, 2.0, 0, 45, true);
		}
			break;
			
		case 5:
		{
			stepX = ofMap(Lev, 0, 2.0, 60, 300, true);
		}
			break;
			
		case 6:
		{
			stepX = ofMap(Lev, 0, 2.0, 0, 300, true);
			
			ofColor temp = color;
			temp.a = ofMap(Lev, 0, 2.0, 0, 120, true);
			color = temp;
		}
			break;
			
		case 7:
		{
			stepX = ofMap(Lev, 0, 2.0, 0, 200, true);
			// stepY = ofMap(Lev, 0, 2.0, 0, 150, true);
			
			ofColor temp = color;
			temp.a = ofMap(Lev, 0, 2.0, 50, 180, true);
			color = temp;
		}
			break;
			
	}
}

/******************************
******************************/
void INDICATOR::SelfRotaion()
{
	float now = ofGetElapsedTimef();
	
	switch(id_pattern){
		case 0:
		case 1:
		{
			const float deg_per_sec = 360.0 / 30.0;
			g_Rotate = now * deg_per_sec;
			
			const float T = 80.0;
			twistX = 45 * sin(2 * PI / T * now);
		}
			break;
			
		case 2:
		{
			const float deg_per_sec = 360.0 / 30.0;
			g_Rotate = now * deg_per_sec;
			
			const float T = 20.0;
			twistY = 5 * sin(2 * PI / T * now);

			twistX = 13 * sin(2 * PI / T * now);
		}
			break;
			
		case 3:
		case 4:
		{
			const float T = 30.0;
			primitive_rotate = 180 * sin(2 * PI / T * now);
		}
			break;
			
		case 5:
		{
			const float deg_per_sec = 360.0 / 30.0;
			g_Rotate = now * deg_per_sec;
			
			const float T = 20.0;
			stepY = 150 * sin(2 * PI / T * now) + 150;
			
			primitive_shiftY = 700 * sin(2 * PI / T * now);
		}
			break;
			
		case 6:
		{
			const float deg_per_sec = 360.0 / 30.0;
			g_Rotate = now * deg_per_sec;

			const float T = 10.0;
			stepY = 70 * sin(2 * PI / T * now) + 70;
		}
			break;
			
		case 7:
		{
			const float deg_per_sec = 360.0 / 60.0;
			g_Rotate = now * deg_per_sec;
			
			const float T = 30.0;
			twistY = 4 * sin(2 * PI / T * now);
		}
			break;
	}
}

/******************************
******************************/
void INDICATOR::stripePattern(double Dj_a)
{
	ofSetColor( color );
	ofSetLineWidth( LineWidth );
	if ( filled ) ofFill(); else ofNoFill();
	
	for (int i=-countX; i<=countX; i++) {
		/********************
		********************/
		AXIS axis;
		
		axis.translate(i * stepX, 0, 0);
		axis.rotate(i * twistX, ofVec3f(0, 0, 1));
		
		axis.translate(0, primitive_shiftY, 0);
		axis.rotate(primitive_rotate, ofVec3f(0, 0, 1));
		
		if(b_PrimitiveSize_by_x)	axis.scale(primitive_size->x, primitive_size->x, 1);
		else						axis.scale(primitive_size->x, primitive_size->y, 1);
		
		/********************
		********************/
		ofVec3f target;
		
		if(type){
			axis.get(ofVec3f(-50, -50, 0), target);
			vbo_Verts[(i + countX) * 4 + 0].set(target);

			axis.get(ofVec3f(-50, 50, 0), target);
			vbo_Verts[(i + countX) * 4 + 1].set(target);

			axis.get(ofVec3f(50, 50, 0), target);
			vbo_Verts[(i + countX) * 4 + 2].set(target);

			axis.get(ofVec3f(50, -50, 0), target);
			vbo_Verts[(i + countX) * 4 + 3].set(target);
			
		}else{
			axis.get(ofVec3f(0, 0, 0), target);
			vbo_Verts[(i + countX) * 3 + 0].set(target);

			axis.get(ofVec3f(-50, 100, 0), target);
			vbo_Verts[(i + countX) * 3 + 1].set(target);

			axis.get(ofVec3f(50, 100, 0), target);
			vbo_Verts[(i + countX) * 3 + 2].set(target);
		}
	}
	
	if(type)	Vbo.updateVertexData(vbo_Verts, (countX * 2 + 1) * 4);
	else		Vbo.updateVertexData(vbo_Verts, (countX * 2 + 1) * 3);
	
	ofColor temp = color;
	for(int i = 0; i < NUM_VERTS; i++){
		vbo_Color[i].set( float(temp.r)/255, float(temp.g)/255, float(temp.b)/255, float(temp.a)/255 * Dj_a);
	}
	Vbo.updateColorData(vbo_Color, NUM_VERTS);
	
	if(type)	Vbo.draw(GL_QUADS, 0, (countX * 2 + 1) * 4);
	else		Vbo.draw(GL_TRIANGLES, 0, (countX * 2 + 1) * 3);
	

	/*
	for (int i=-countX; i<=countX; i++) {
		ofPushMatrix();
		ofTranslate( i * stepX, 0 );
		ofRotate( i * twistX );
		
		ofTranslate( 0, primitive_shiftY );
		ofRotate( primitive_rotate );
		
		if(b_PrimitiveSize_by_x)	ofScale( primitive_size->x, primitive_size->x );
		else						ofScale( primitive_size->x, primitive_size->y );
		
		ofTriangle( 0, 0, -50, 100, 50, 100 );
		// ofRect( -50, -50, 100, 100 );
		
		ofPopMatrix();
	}
	*/
}

/******************************
******************************/
void INDICATOR::matrixPattern(double Dj_a)
{
	for (int y=-countY; y<=countY; y++) {
		ofPushMatrix();

		if ( countY > 0 ) { // if countY is set.
			float scl = ofMap( y, -countY, countY, 1-pinchY, 1 );
			ofScale( scl, scl );
		}
		ofTranslate( 0, y * stepY );
		ofRotate( y * twistY );
		stripePattern(Dj_a);
		
		ofPopMatrix();
	}
}

/******************************
******************************/
void INDICATOR::RandomSet_Pattern()
{
	/********************
	********************/
	id_pattern = rand() % NUM_PATTERNS;
	printf("Indicator = %d\n", id_pattern);
	
	/********************
	********************/
	LoadXmlParameter();
	
	/********************
	********************/
	if(BootMode == MODE_DEMO){
		MusicSync = true;
		b_SelfRotation = true;
	}
}

/******************************
description
	alpha	LoadXmlParameter()	で決定
	color	set_color()			で決定
******************************/
void INDICATOR::LoadXmlParameter()
{
	/********************
	********************/
	ofColor keep_color = color;
	bool keep_MusicSync = MusicSync;
	bool keep_b_SelfRotation = b_SelfRotation;
	
	/********************
	load
	********************/
	char FileName[BUF_SIZE];
	sprintf(FileName, "Indicator/%d.xml", id_pattern);
	gui.loadFromFile(FileName);
	
	/********************
	RGBはkeepするが、Alphaは模様によって最適に設定された値がxmlに格納されているので、これを使う。
	********************/
	ofColor xml_color = color;
	keep_color.a = xml_color.a;
	color = keep_color;
	
	MusicSync = keep_MusicSync;
	b_SelfRotation = keep_b_SelfRotation;
}

/******************************
******************************/
void INDICATOR::draw(double Dj_a)
{
	ofPushStyle();
	
	/********************
	********************/
	// ofBackground(0, 0, 0, 0);
	
	/********************
	********************/
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	/********************
	********************/
	ofSetColor(255, 255, 255, 255);
	
	/********************
	********************/
	ofPushMatrix();
	ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
	float Scl = pow( g_Scale, 4.0f );
	ofScale( Scl, Scl );
	ofRotate( g_Rotate );

	matrixPattern(Dj_a);
	
	ofPopMatrix();
	
	
	if ( showGui ) gui.draw();
	
	ofPopStyle();
}

/******************************
description
	alpha	LoadXmlParameter()	で決定
	color	set_color()			で決定
******************************/
void INDICATOR::set_color(COLORPATTERNS colorTheme)
{
	ofColor temp = color;
	
	switch(colorTheme){
		case COLPATTERN_AQUA:
		{
			color = ofColor(50, 50, 255, temp.a);
		}
			break;
			
		case COLPATTERN_MAGMA:
		{
			color = ofColor(255, 50, 50, temp.a);
		}
			break;
			
		case COLPATTERN_DIGITAL:
		{
			color = ofColor(50, 255, 110, temp.a);
		}
			break;
			
		case COLPATTERN_SEXY:
		{
			color = ofColor(110, 25, 255, temp.a);
		}
			break;
			
		case COLPATTERN_TRIP:
		{
			int RandomNum = rand() % 2;
			
			if(RandomNum == 0){
				color = ofColor(255, 25, 25, temp.a);
			}else{
				color = ofColor(25, 25, 255, temp.a);
			}
		}
			break;
			
		case COLPATTERN_REGGAE:
		{
			int RandomNum = rand() % 3;
			
			if(RandomNum == 0){
				color = ofColor(255, 255, 30, temp.a);
			}else if(RandomNum == 1){
				color = ofColor(255, 25, 25, temp.a);
			}else{
				color = ofColor(25, 255, 25, temp.a);
			}
		}
			break;
			
		case COLPATTERN_SAMBA:
		{
			int RandomNum = rand() % 3;
			
			if(RandomNum == 0){
				color = ofColor(25, 25, 255, temp.a);
			}else if(RandomNum == 1){
				color = ofColor(25, 255, 25, temp.a);
			}else{
				color = ofColor(255, 25, 25, temp.a);
			}
		}
			break;
			
		case COLPATTERN_SWEETS:
		{
			int RandomNum = rand() % 2;
			
			if(RandomNum == 0){
				color = ofColor(255, 255, 25, temp.a);
			}else{
				color = ofColor(255, 25, 255, temp.a);
			}
		}
			break;
	}
}

/******************************
******************************/
void INDICATOR::keyPressed(int key)
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
			id_pattern = key - '0';
			LoadXmlParameter();
		}
			break;
			
		case 'd':
			showGui = !showGui;
			break;
			
		case 'r':
			id_pattern = -1;
			gui.loadFromFile( "Indicator/reset.xml" );
			break;
			
		case 's':
			if(showGui) gui.saveToFile("indicator.xml");
			break;
	}
	
	printf("return to Normal key\n");
}

