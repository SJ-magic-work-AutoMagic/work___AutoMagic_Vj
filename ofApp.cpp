/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _BootMode)
: OscDj("127.0.0.1", 12348, 12349)
, OscLiveVideoServer("127.0.0.1", 12356, 12355)

// , Osc_AcsMotion("127.0.0.1", 15001, 15000)
// , Osc_AcsMotion("10.0.0.1", 15001, 15000)	// when not connected, app crashes.
												// 127.0.0.1 is OK.

, b_test_ChangeContents(false)
, b_1stUdpMessage(true)
, b_fullScreen(false)
, particle(PARTICLE_SET::getInstance())
, Indicator(INDICATOR::getInstance())
, Text(TEXT::getInstance())
, Strobe(STROBE::getInstance())
// , Cg(CG::getInstance())
, b_UseLiveVideo(false)

#ifdef SJ_REC
, t_1st_OscMessage_ColorTheme(-1)
#endif
{
	BootMode = BOOT_MODE(_BootMode);
	
	OscVideoServer[0].setup("127.0.0.1", 12352, 12351);
	OscVideoServer[1].setup("127.0.0.1", 12354, 12353);
	
	if(BootMode == MODE_TEST)	b_DispFrameRate = true;
	else						b_DispFrameRate = false;
}

/******************************
******************************/
ofApp::~ofApp()
{
}

/******************************
******************************/
void ofApp::exit()
{
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	srand((unsigned) time(NULL));
	
	/********************
	********************/
	ofSetWindowTitle( "Vj" );
	ofSetWindowShape( WIDTH, HEIGHT );
	
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	shader_VideoMix.load( "VideoMix/Vert.c", "VideoMix/Frag.c" );
	
	/********************
	********************/
	for(int i = 0; i < NUM_VIDEO_SERVES; i++){
		for(int j = 0; j < NUM_VIDEOS_PER_SERVER; j++){
			video_client[i][j].setup();
			
			char buf[BUF_SIZE];
			sprintf(buf, "Server_%d_%d", i, j);
			video_client[i][j].set(buf, "AutoMagic_VideoServer"); // void set(string _serverName, string _appName);
		}
		
		/* */
		b_ServerReady[i] = true;
	}
	
	/* */
	LiveVideo_client.setup();
	LiveVideo_client.set("LiveVideoServer", "AutoMagic_LiveVideoServer"); // void set(string _serverName, string _appName);
	
	/********************
	********************/
	mainOutputSyphonServer.setName("Vj Screen Output");
	
	/********************
	********************/
	udpConnection.Create();
	udpConnection.Bind(UDP_RECEIVE_PORT);
	udpConnection.SetNonBlocking(true);
	
	/********************
	********************/
	id_VideoServer = 0;
	setup_gui();
	
	/********************
	********************/
	for(int i = 0; i < NUM_VIDEOS_PER_SERVER; i++){
		fbo[i].allocate( ofGetWidth(), ofGetHeight() , GL_RGBA);
	}
	fbo_Effect_0.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo_VideoMix.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA);
	
	/********************
	********************/
	mov0_Effect.setup();
	mov_Effect.setup();
	particle->setup();
	Indicator->setup();
	Text->setup();
	Strobe->setup();
	// Cg->setup();
	
	/********************
	********************/
	img_jacket.load("jacket.png");
}

/******************************
******************************/
void ofApp::setup_gui(){
	/********************
	********************/
	b_DispGui = true;
	
	/********************
	********************/
	gui.setup();
	
	/* Udp */
	gui.add(gui__mov_a.setup("mov_a", 1.0, 0, 1.0));
	gui.add(gui__b_mov_Effect_On.setup("b_mov_Effect_On", false));
	gui.add(gui__mov_a_0_12.setup("mov_a_0_12", 0, 0, 1.0));
	gui.add(gui__b_mov0_Effect_On.setup("b_mov0_Effect_On", false));
	gui.add(gui__mov_a_1_2.setup("mov_a_1_2", 0, 0, 1.0));
	gui.add(gui__a_indicator.setup("a_indicator", 0, 0, 1.0));
	gui.add(gui__a_particle.setup("a_particle", 0, 0, 1.0));
	gui.add(gui__b_GeneratedImage_on.setup("b_GeneratedImage_on", false));
	gui.add(gui__b_text_on.setup("b_text_on", false));
	gui.add(gui__a_Strobe.setup("a_Strobe", 0, 0, 1.0));
	gui.add(gui__a_Cg.setup("a_Cg", 1.0, 0, 1.0));
	
	/* original inside. */
	gui.add(gui__b_Mix_mov12_add.setup("b_Mix_mov12_add", false));
	
	/* */
	gui.add(gui__a_Jacket.setup("a_Jacket", 0, 0, 1.0));
	gui.add(gui__b_Mix_Jacket_add.setup("b_Mix_Jacket_add", false));
}

/******************************
******************************/
void ofApp::Res_OscFrom_VideoServer()
{
	for(int i = 0; i < NUM_VIDEO_SERVES; i++){
		while(OscVideoServer[i].OscReceive.hasWaitingMessages()){
			ofxOscMessage m_receive;
			OscVideoServer[i].OscReceive.getNextMessage(&m_receive);
			
			if(m_receive.getAddress() == "/Ready_CallBack"){
				m_receive.getArgAsInt32(0); // 読み捨て
				
				b_ServerReady[i] = true;
			}
		}
	}
}

/******************************
******************************/
void ofApp::ChangeCgId_OscFrom_AcsMotion()
{
/*
	while(Osc_AcsMotion.OscReceive.hasWaitingMessages()){
		ofxOscMessage m_receive;
		Osc_AcsMotion.OscReceive.getNextMessage(&m_receive);
		
		if(m_receive.getAddress() == "/Motion"){
			int MotionId = m_receive.getArgAsInt32(0);
			
			int temp_i		= m_receive.getArgAsInt32(1);
			float temp_f	= m_receive.getArgAsFloat(2);
			temp_f			= m_receive.getArgAsFloat(3);
			
			Cg->ChangeId(MotionId);
		}
	}
*/
}

/******************************
******************************/
void ofApp::Res_OscFrom_Dj()
{
	while( (BootMode == MODE_DEMO) && OscDj.OscReceive.hasWaitingMessages() ){
		ofxOscMessage m_receive;
		OscDj.OscReceive.getNextMessage(&m_receive);
		
		/********************
		********************/
		if(m_receive.getAddress() == "/AreYouReady"){
			m_receive.getArgAsInt32(0); // 読み捨て
			
			/* always yes. */
			ofxOscMessage m_send;
			m_send.setAddress("/Ready");
			m_send.addIntArg(1); // yes.
			OscDj.OscSend.sendMessage(m_send);
			
		}else if(m_receive.getAddress() == "/Quit"){
			/* */
			ofxOscMessage m_send;
			m_send.setAddress("/Quit");
			m_send.addIntArg(1);
			
			for(int i = 0; i < NUM_VIDEO_SERVES; i++) OscVideoServer[i].OscSend.sendMessage(m_send);
			OscLiveVideoServer.OscSend.sendMessage(m_send);
			
			/* */
			std::exit(1);
			
		}else if(m_receive.getAddress() == "/VJContentsChange"){
			m_receive.getArgAsInt32(0); // 読み捨て
			
			ContentsChange();
			
		}else if(m_receive.getAddress() == "/VJColorTheme"){
			int ColorThemeID = m_receive.getArgAsInt32(0);
			
			ColorChange(COLORPATTERNS(ColorThemeID));
			
#ifdef SJ_REC
		if(t_1st_OscMessage_ColorTheme == -1){
			t_1st_OscMessage_ColorTheme = ofGetElapsedTimef();
		}
#endif
			
		}else if(m_receive.getAddress() == "/VJ_BpmInfo"){
			int BeatInterval_ms = m_receive.getArgAsInt32(0);
			Text->set_RefreshRate(BeatInterval_ms);
		}
	}
}

/******************************
******************************/
void ofApp::get_UdpMessage_From_Dj()
{
	char udpMessage[SIZE_UPD];
	udpConnection.Receive(udpMessage,SIZE_UPD);
	string message=udpMessage;
	if(message!=""){
		/********************
		********************/
		vector<string> params = ofSplitString(message, "|");
		
		/********************
		********************/
		vector<string> alphas = ofSplitString(params[0], ",");
		if( (BootMode == MODE_DEMO) && (alphas.size() == 10) ){
			DataSet_Alpha.mov_a					= atof(alphas[0].c_str());
			DataSet_Alpha.b_mov_Effect_On		= atoi(alphas[1].c_str());
			DataSet_Alpha.mov_a_0_12			= atof(alphas[2].c_str());
			DataSet_Alpha.b_mov0_Effect_On		= atoi(alphas[3].c_str());
			DataSet_Alpha.mov_a_1_2				= atof(alphas[4].c_str());
			DataSet_Alpha.a_indicator			= atof(alphas[5].c_str());
			DataSet_Alpha.a_particle			= atof(alphas[6].c_str());
			DataSet_Alpha.b_GeneratedImage_on	= atoi(alphas[7].c_str());
			DataSet_Alpha.b_text_on				= atoi(alphas[8].c_str());
			DataSet_Alpha.a_Strobe				= atof(alphas[9].c_str());
			
			ApplyUdp_ToGui_for_Monitoring();
		}
		
		/********************
		********************/
		vector<string> fft = ofSplitString(params[1], ",");
		if(b_1stUdpMessage){
			b_1stUdpMessage = false;
			spectrum.resize(fft.size() - 1);
			
			printf("fft size = %d\n", int(spectrum.size()));
		}
		if(fft.size() - 1 == spectrum.size()){
			for(int i = 0; i < spectrum.size(); i++){
				spectrum[i] = atof(fft[i].c_str());
			}
		}
		
		/********************
		********************/
		while(message != ""){
			udpConnection.Receive(udpMessage,SIZE_UPD);
			message = udpMessage;
		}
	}
}

/******************************
******************************/
void ofApp::ApplyUdp_ToGui_for_Monitoring()
{
	gui__mov_a = DataSet_Alpha.mov_a;
	gui__b_mov_Effect_On = DataSet_Alpha.b_mov_Effect_On;
	gui__mov_a_0_12 = DataSet_Alpha.mov_a_0_12;
	gui__b_mov0_Effect_On = DataSet_Alpha.b_mov0_Effect_On;
	gui__mov_a_1_2 = DataSet_Alpha.mov_a_1_2;
	gui__a_indicator = DataSet_Alpha.a_indicator;
	gui__a_particle = DataSet_Alpha.a_particle;
	gui__b_GeneratedImage_on = DataSet_Alpha.b_GeneratedImage_on;
	gui__b_text_on = DataSet_Alpha.b_text_on;
	gui__a_Strobe = DataSet_Alpha.a_Strobe;
	
	// gui__a_Cg = DataSet_Alpha.a_Cg;
}

/******************************
description
	No overwrite fft.
******************************/
void ofApp::overWrite_Dataset_getFromDjUdp_with_gui()
{
	DataSet_Alpha.mov_a					= gui__mov_a;
	DataSet_Alpha.b_mov_Effect_On		= gui__b_mov_Effect_On;
	DataSet_Alpha.mov_a_0_12			= gui__mov_a_0_12;
	DataSet_Alpha.b_mov0_Effect_On		= gui__b_mov0_Effect_On;
	DataSet_Alpha.mov_a_1_2				= gui__mov_a_1_2;
	DataSet_Alpha.a_indicator			= gui__a_indicator;
	DataSet_Alpha.a_particle			= gui__a_particle;
	DataSet_Alpha.b_GeneratedImage_on	= gui__b_GeneratedImage_on;
	DataSet_Alpha.b_text_on				= gui__b_text_on;
	DataSet_Alpha.a_Strobe				= gui__a_Strobe;
	DataSet_Alpha.a_Cg					= gui__a_Cg;
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	Res_OscFrom_VideoServer();
	
	Res_OscFrom_Dj();
	
	get_UdpMessage_From_Dj();
	
	// ChangeCgId_OscFrom_AcsMotion();
	
	/********************
	********************/
	if(BootMode == MODE_TEST){
		/********************
		********************/
		overWrite_Dataset_getFromDjUdp_with_gui();
		
		/********************
		********************/
		if(b_test_ChangeContents){
			b_test_ChangeContents = false;
			
			ContentsChange();
		}
	}	
	
	/********************
	update class objects.
	********************/
	mov0_Effect.update();
	mov_Effect.update();
	particle->update(DataSet_Alpha.a_particle);
	Indicator->update(spectrum);
	Text->update();
	Strobe->update();
	
	// Cg->update();
}

/******************************
******************************/
void ofApp::ContentsChange()
{
	printMessage("Contents Change");
	
	/********************
	********************/
	try_VideoContentsChange();
	
	/********************
	mov_Effect, ...は、必ずContents change.
	********************/
	MOV_EFFECT::RandomSet_EffectType_Combination(mov_Effect, mov0_Effect);
	
	particle->RandomSet_GravityPosition();
	Indicator->RandomSet_Pattern();
	Text->RandomSet_Text();
	Strobe->RandomSet_StrobeType();
	
	RandomSet_VideoMix();
}

/******************************
******************************/
void ofApp::RandomSet_VideoMix()
{
	/********************
	********************/
	enum{
		MOV12_MIX_ALPHA,
		MOV12_MIX_ADD,
		
		NUM_MIXTYPE,
	};
	int weight[NUM_MIXTYPE] = {1, 1};
	int mixType = Dice_index(weight, NUM_MIXTYPE);
	
	gui__b_Mix_mov12_add = bool(mixType);
}

/******************************
******************************/
void ofApp::ColorChange(COLORPATTERNS id)
{
	/********************
	********************/
	printMessage("Color Change");
	switch(id){
		case COLPATTERN_AQUA:
			printf("AQUA\n");
			break;
		case COLPATTERN_MAGMA:
			printf("MAGMA");
			break;
		case COLPATTERN_DIGITAL:
			printf("DIGITAL");
			break;
		case COLPATTERN_SEXY:
			printf("SEXY");
			break;
		case COLPATTERN_TRIP:
			printf("TRIP");
			break;
		case COLPATTERN_REGGAE:
			printf("REGGAE");
			break;
		case COLPATTERN_SAMBA:
			printf("SAMBA");
			break;
		case COLPATTERN_SWEETS:
			printf("SWEETS");
			break;
	}

	
	/********************
	********************/
	particle->set_color( id );
	Indicator->set_color( id );
	// Cg->set_color( id );
}

/******************************
******************************/
void ofApp::try_VideoContentsChange()
{
	int NextVideoServerId = get_NextVideoServerId(id_VideoServer);
	if(b_ServerReady[NextVideoServerId]){
		/********************
		********************/
		b_ServerReady[id_VideoServer] = false;
		
		ofxOscMessage m_send;
		m_send.setAddress("/VJContentsChange");
		m_send.addIntArg(1);
		OscVideoServer[id_VideoServer].OscSend.sendMessage(m_send);
		
		id_VideoServer = NextVideoServerId;
		
		/********************
		********************/
		printf("changed video server.\n");
		
	}else{
		printf("Next video server not ready.\n");
	}
}

/******************************
******************************/
int ofApp::get_NextVideoServerId(int id)
{
	id++;
	if(NUM_VIDEO_SERVES <= id){
		id = 0;
	}
	return id;
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0, 0, 0, 0);
	ofSetColor(255, 255, 255, 255);

	/********************
	video serverからfbo[]に3面分のvideo画面を取ってくる。
	********************/
	for(int i = 0; i < NUM_VIDEOS_PER_SERVER; i++){
		fbo[i].begin();
		ofBackground(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		ofDisableAlphaBlending();
		
		if( (i == 0) && (b_UseLiveVideo) ){
			LiveVideo_client.draw(0, 0);
		}else{
			// video_client[id_VideoServer][i].draw(0, 0, fbo[i].getWidth(), fbo[i].getHeight());
			video_client[id_VideoServer][i].draw(0, 0); // w, h を指定すると、videoが来ていない時の画面が何故か白くなった. 黒くするためにこちらのcodeを採用.
		}
		
		fbo[i].end();
	}
	
	/********************
	********************/
	/* add effect to fbo[0] */
	mov0_Effect.draw(DataSet_Alpha.b_mov0_Effect_On, &fbo[0], &fbo_Effect_0);
	
	/* mix 3 images */
	draw_MixVideo();
	
	/********************
	********************/
	mov_Effect.draw(DataSet_Alpha.b_mov_Effect_On, &fbo_VideoMix);
	
	/********************
	********************/
	if(DataSet_Alpha.b_GeneratedImage_on){ // for saving CPU power.
		particle->draw(); // as for particle, set alpha at update() method.
		Indicator->draw(DataSet_Alpha.a_indicator);
	}
	
	if(DataSet_Alpha.b_text_on){
		Text->draw();
	}
	
	Strobe->draw(DataSet_Alpha.a_Strobe);
	
	// Cg->draw(gui__a_Cg); // not received from Dj now(will be implemented).
	
	/********************
	********************/
	ofPushStyle();
		ofEnableAlphaBlending();
		if(gui__b_Mix_Jacket_add)	ofEnableBlendMode(OF_BLENDMODE_ADD);
		else						ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		
		ofSetColor(255, 255, 255, int(255 * gui__a_Jacket));
		
		img_jacket.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofPopStyle();
	
	/********************
	********************/
	if(b_DispGui) gui.draw();
	
	if(b_DispFrameRate){
		ofSetColor(255, 255, 255, 150);
		
		char buf[BUF_SIZE];
		sprintf(buf, "FrameRate = %5.1f", ofGetFrameRate());
		ofDrawBitmapString(buf, 10, 10);
	}
	
	/********************
	********************/
#ifdef SJ_REC
	if(0 <= t_1st_OscMessage_ColorTheme){
		float dt = ofGetElapsedTimef() - t_1st_OscMessage_ColorTheme;
		if(dt < 5.0){
			char TimeFrom_1stMessage[BUF_SIZE];
			sprintf(TimeFrom_1stMessage, "%7.2f", dt);
			
			ofDrawBitmapString(TimeFrom_1stMessage, 10, 20);
		}
	}
#endif

	/********************
	********************/
	mainOutputSyphonServer.publishScreen();
}

/******************************
description
	細かく言うと、
		DataSet_Alpha
			b_mov_Effect_On
			b_mov0_Effect_On
			a_indicator
			a_particle
	も含めて設定する所だが、color movieにGenerate Imageが乗るケースも普通に面白いので、
	あえて、緩めの条件にしておく。
******************************/
bool ofApp::IsMov_Gray()
{
	if( (DataSet_Alpha.b_GeneratedImage_on) && (MOV_EFFECT::IsGray()) )	return true;
	else																return false;
}

/******************************
******************************/
int ofApp::draw_MixVideo()
{
	fbo_VideoMix.begin();
	shader_VideoMix.begin();
	
	ofBackground(0, 0, 0);
	ofSetColor(255, 255, 255, 255);
	ofDisableAlphaBlending();
	
	shader_VideoMix.setUniform1f( "mov_a", DataSet_Alpha.mov_a );
	shader_VideoMix.setUniform1f( "mov_a_0_12", DataSet_Alpha.mov_a_0_12 );
	shader_VideoMix.setUniform1f( "mov_a_1_2", DataSet_Alpha.mov_a_1_2 );
	shader_VideoMix.setUniform1f( "b_Gray", IsMov_Gray() );
	shader_VideoMix.setUniform1f( "b_Mix_mov12_add", gui__b_Mix_mov12_add );
	
	shader_VideoMix.setUniformTexture( "texture1", fbo[1].getTextureReference(), 1 ); 
	shader_VideoMix.setUniformTexture( "texture2", fbo[2].getTextureReference(), 2 ); 
	
	fbo_Effect_0.draw(0, 0); // texture0
	
	shader_VideoMix.end();
	fbo_VideoMix.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/********************
	********************/
	enum INPUT_STATE{
		INPUT_NORMAL,
		
		INPUT_PARTICLE,
		INPUT_INDICATOR,
		INPUT_TEXT,
		INPUT_STROBE,
		INPUT_MOV_EFFECT,
		
		INPUT_3DCG,
	};
	static INPUT_STATE InputState = INPUT_NORMAL;
	
	/********************
	********************/
	if(InputState == INPUT_NORMAL){
		switch(key){
			case '0': // COLPATTERN_AQUA,
			case '1': // COLPATTERN_MAGMA,
			case '2': // COLPATTERN_DIGITAL,
			case '3': // COLPATTERN_SEXY,
			case '4': // COLPATTERN_TRIP,
			case '5': // COLPATTERN_REGGAE,
			case '6': // COLPATTERN_SAMBA,
			case '7': // COLPATTERN_SWEETS,
			
				ColorChange(COLORPATTERNS(key - '0') );
				break;
			
			case 'c':
				b_test_ChangeContents = true;
				break;
				
			case 'd':
				b_DispGui = !b_DispGui;
				break;
				
			case 'e':
				InputState = INPUT_MOV_EFFECT;
				printMessage("key for Mov Effect");
				break;
				
			case 'f':
				b_fullScreen = !b_fullScreen;
				ofSetFullscreen(b_fullScreen);
				if(!b_fullScreen){
					ofSetWindowShape( WIDTH, HEIGHT );
				}
				break;
				
			case 'g':
				InputState = INPUT_3DCG;
				printMessage("key for 3D CG");
				break;
				
			case 'i':
				if(DataSet_Alpha.b_GeneratedImage_on){
					InputState = INPUT_INDICATOR;
					printMessage("key for Indicator");
				}else{
					printf("Please Enable Generated Image = ON\n");
				}
				break;
				
			case 'p':
				if(DataSet_Alpha.b_GeneratedImage_on){
					InputState = INPUT_PARTICLE;
					printMessage("key for particle");
				}else{
					printf("Please Enable Generated Image = ON\n");
				}
				break;
				
			case 's':
				InputState = INPUT_STROBE;
				printMessage("key for strobe");
				break;
				
			case 't':
				InputState = INPUT_TEXT;
				printMessage("key for text");
				break;
				
			case 'v':
				b_UseLiveVideo = !b_UseLiveVideo;
				printMessage("Live Video");
				printf("%d\n", b_UseLiveVideo);
				break;
				
			case 'r':
				b_DispFrameRate = !b_DispFrameRate;
				break;
				
			case ' ':
			{
				ofImage image;
				image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
				image.saveImage("screen.png");
			}
				break;
				
			case '-':
				ofSetWindowShape( WIDTH_SMALL, HEIGHT_SMALL );
				break;
		}
		
	}else if(InputState == INPUT_PARTICLE){
		particle->keyPressed(key);
		InputState = INPUT_NORMAL;
		
	}else if(InputState == INPUT_INDICATOR){
		Indicator->keyPressed(key);
		InputState = INPUT_NORMAL;
		
	}else if(InputState == INPUT_TEXT){
		Text->keyPressed(key);
		InputState = INPUT_NORMAL;
		
	}else if(InputState == INPUT_STROBE){
		Strobe->keyPressed(key);
		InputState = INPUT_NORMAL;
		
	}else if(InputState == INPUT_MOV_EFFECT){
		mov0_Effect.keyPressed(key);
		mov_Effect.keyPressed(key);
		InputState = INPUT_NORMAL;
		
	}else if(InputState == INPUT_3DCG){
		// Cg->keyPressed(key);
		InputState = INPUT_NORMAL;
		
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
