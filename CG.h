/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

#include "sjCommon.h"

/************************************************************
************************************************************/

class CG{
private:
	/****************************************
	****************************************/
	enum DRAW_TYPE{
		DRAW_TYPE__FACE,
		DRAW_TYPE__POINTS,
		DRAW_TYPE__WIREFRAME,
	};
	
	enum MOTIONTYPE{
		MOTIONTYPE__LOOP,
		
		MOTIONTYPE__LACOSTE,
		MOTIONTYPE__MAENORI,
		MOTIONTYPE__SLIDE,
		MOTIONTYPE__BIZ,
		MOTIONTYPE__BIZ_SKIN,
		
		NUM_MOTIONTYPES,
	};
	
	class CHANGE_ID_BY_KEY{
	private:
		bool b_Change;
		int NewMotionId;
	public:
		CHANGE_ID_BY_KEY()
		: b_Change(false)
		{
		}
		
		void set_NewId(int _id){
			NewMotionId = _id;
			b_Change = true;
		}
		
		int get_NewId(){
			b_Change = false;
			return NewMotionId;
		}
		
		bool Is_setNewId(){
			return b_Change;
		}
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
	bool b_Enable;
	int MotionId;
	DRAW_TYPE DrawType;
	
	CHANGE_ID_BY_KEY ChangeId_ByKeyboard;
	
	ofxAssimpModelLoader model[NUM_MOTIONTYPES];
	ofxAssimpAnimation *modelAnimation[NUM_MOTIONTYPES];
	
	/********************
	********************/
	ofEasyCam camera;
	bool b_cam_orbit;
	
	ofFbo fbo;
	
	double CamDistane_Still;
	
	/********************
	********************/
	ofLight PointLight;
	
	/********************
	GUI
	********************/
	bool b_DispGui;
	
	/* */
	ofxPanel gui;
	
	ofxToggle b_DispLight;
	
	/*  */
	ofxGuiGroup guiGp_point;
	ofxColorSlider pointColor_diffuse;
	ofxColorSlider pointColor_specular;
	ofxVec3Slider point_position;
	ofxFloatSlider point_attenuation_constant;
	ofxFloatSlider point_attenuation_linear;
	ofxFloatSlider point_attenuation_quadratic;
	
	/* */
	ofxGuiGroup guiGp_CamOrbit;
	ofxVec3Slider cam_Target;
	ofxFloatSlider cam_Speed;
	ofxFloatSlider cam_latitude;
	ofxFloatSlider cam_radius;
	
	
	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	CG();
	~CG();
	CG(const CG&); // Copy constructor. no define.
	CG& operator=(const CG&); // コピー代入演算子. no define.
	
	/********************
	********************/
	void setup_gui();
	void apply_gui_parameter();
	void check_if_FileExist(char* FileName);
	void cam_orbit_motion();
	
	
public:
	/****************************************
	****************************************/
	static CG* getInstance(){
		static CG inst;
		return &inst;
	}
	
	
	void setup();
	void update();
	void draw(double Cg_a);
	void keyPressed(int key);
	
	void ChangeId(int _MotionId);
	
	void set_color(COLORPATTERNS colorTheme);
};
