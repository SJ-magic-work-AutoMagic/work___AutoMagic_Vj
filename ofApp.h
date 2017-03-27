/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"
#include "ofxSyphon.h"
#include "ofxGui.h"

#include "sjCommon.h"
#include "movEffect.h"
#include "particle.h"
#include "Indicator.h"
#include "Text.h"
#include "Strobe.h"
#include "CG.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class OSC_SEND{
private:
	char IP[BUF_SIZE];
	int Port;

	ofxOscSender sender;
	
public:
	OSC_SEND()
	: Port(-1)
	{
	}
	OSC_SEND(const char* _IP, int _Port)
	{
		if(_Port != -1){
			sprintf(IP, "%s", _IP);
			Port = _Port;
			
			sender.setup(IP, Port);
		}
	}
	
	void setup(const char* _IP, int _Port)
	{
		if(_Port != -1){
			sprintf(IP, "%s", _IP);
			Port = _Port;
			
			sender.setup(IP, Port);
		}
	}
	void sendMessage(ofxOscMessage &message)
	{
		if(Port != -1){
			sender.sendMessage(message);
		}
	}
};

class OSC_RECEIVE{
private:
	int Port;
	ofxOscReceiver	receiver;
	
public:
	OSC_RECEIVE()
	: Port(-1)
	{
	}
	OSC_RECEIVE(int _Port)
	{
		if(_Port != -1){
			Port = _Port;
			receiver.setup(Port);
		}
	}
	
	void setup(int _Port)
	{
		if(_Port != -1){
			Port = _Port;
			receiver.setup(Port);
		}
	}
	
	bool hasWaitingMessages()
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.hasWaitingMessages();
		}
	}
	
	bool getNextMessage(ofxOscMessage *msg)
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.getNextMessage(msg);
		}
	}
};

class OSC_TARGET{
private:
public:
	OSC_SEND	OscSend;
	OSC_RECEIVE	OscReceive;
	
	OSC_TARGET()
	{
	}
	
	OSC_TARGET(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	: OscSend(_SendTo_IP, _SendTo_Port), OscReceive(_Receive_Port)
	{
	}
	
	void setup(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	{
		OscSend.setup(_SendTo_IP, _SendTo_Port);
		OscReceive.setup(_Receive_Port);
	}
};

/**************************************************
**************************************************/
struct DATASET__ALPHA{
	/****************************************
	****************************************/
	double	mov_a;
	bool	b_mov_Effect_On;
	double	mov_a_0_12;
	bool	b_mov0_Effect_On;
	double	mov_a_1_2;
	double	a_indicator;
	double	a_particle;
	bool	b_GeneratedImage_on;
	bool	b_text_on;
	double	a_Strobe;
	
	double	a_Cg;
	
	/****************************************
	****************************************/
	DATASET__ALPHA()
	: mov_a(0), b_mov_Effect_On(false), mov_a_0_12(0), b_mov0_Effect_On(false), mov_a_1_2(0), a_indicator(0), a_particle(0), b_GeneratedImage_on(false), b_text_on(false), a_Strobe(0), a_Cg(0)
	{
	}
};

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WIDTH = 1280,
		HEIGHT = 720,
		
		WIDTH_SMALL = 960,
		HEIGHT_SMALL = 540,
	};
	enum{
#ifdef ONE_VIDEO_SERVER
		NUM_VIDEO_SERVES = 1,
#else
		NUM_VIDEO_SERVES = 2,
#endif

		NUM_VIDEOS_PER_SERVER = 3,
	};
	enum{
		UDP_RECEIVE_PORT = 12350,
		SIZE_UPD = 100000,
	};
	
	/****************************************
	****************************************/

	/********************
	********************/
	ofxSyphonServer mainOutputSyphonServer;
	
	/********************
	********************/
	OSC_TARGET OscDj;
	OSC_TARGET OscVideoServer[NUM_VIDEO_SERVES];
	OSC_TARGET OscLiveVideoServer;
	OSC_TARGET Osc_AcsMotion;
	
	ofxUDPManager udpConnection;
	
	ofxSyphonClient video_client[NUM_VIDEO_SERVES][NUM_VIDEOS_PER_SERVER];
	bool b_ServerReady[NUM_VIDEO_SERVES];
	int id_VideoServer;
	
	ofxSyphonClient LiveVideo_client;
	bool b_UseLiveVideo;
	
	vector<float> spectrum;
	bool b_1stUdpMessage;
	
	DATASET__ALPHA DataSet_Alpha;
	
	ofFbo fbo[NUM_VIDEOS_PER_SERVER];
	ofFbo fbo_Effect_0;
	ofFbo fbo_VideoMix;
	
	ofShader shader_VideoMix;
	
	/********************
	********************/
	MOV_EFFECT mov0_Effect;
	MOV_EFFECT mov_Effect;
	
	PARTICLE_SET* particle;
	INDICATOR* Indicator;
	TEXT* Text;
	STROBE* Strobe;
	CG* Cg;
	
	ofImage img_jacket;
	
	
	/********************
	********************/
	ofxPanel gui;
	
	/* Udp */
	ofxFloatSlider gui__mov_a;
	ofxToggle gui__b_mov_Effect_On;
	ofxFloatSlider gui__mov_a_0_12;
	ofxToggle gui__b_mov0_Effect_On;
	ofxFloatSlider gui__mov_a_1_2;
	ofxFloatSlider gui__a_indicator;
	ofxFloatSlider gui__a_particle;
	ofxIntSlider gui__ParticlePos;
	ofxToggle gui__b_GeneratedImage_on;
	ofxToggle gui__b_text_on;
	ofxFloatSlider gui__a_Strobe;
	ofxFloatSlider gui__a_Cg;
	
	ofxFloatSlider gui__a_Jacket;
	ofxToggle gui__b_Mix_Jacket_add;

	/* original inside. */
	ofxToggle gui__b_Mix_mov12_add;
	
	
	/* */
	bool b_DispGui;
	
	/********************
	********************/
	bool b_test_ChangeContents;
	
	bool b_fullScreen;
	bool b_DispFrameRate;

	/********************
	********************/
#ifdef SJ_REC
	float t_1st_OscMessage_ColorTheme;
#endif	
	
	
	/****************************************
	****************************************/
	int get_NextVideoServerId(int id);
	void setup_gui();
	void try_VideoContentsChange();
	int draw_MixVideo();
	void ContentsChange();
	void ColorChange(COLORPATTERNS id);
	
	void Res_OscFrom_VideoServer();
	void ChangeCgId_OscFrom_AcsMotion();
	void Res_OscFrom_Dj();
	void get_UdpMessage_From_Dj();
	void overWrite_Dataset_getFromDjUdp_with_gui();
	void ApplyUdp_ToGui_for_Monitoring();
	
	void RandomSet_VideoMix();
	bool IsMov_Gray();
	
public:
	/****************************************
	****************************************/
	ofApp(int _BootMode);
	~ofApp();
	void exit();
	
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
