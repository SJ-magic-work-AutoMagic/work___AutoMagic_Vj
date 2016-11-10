/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

#include "sjCommon.h"

/************************************************************
************************************************************/

/**************************************************
description
	基底ベクトルを定義し、これに対し、
	translate, rotat, scale
	のmethodを準備。
	
	さらに、変換後の空間上での(x, y, z)が、正規直交空間ではどの座標になるか、を取得するmethod(get())も準備した
**************************************************/
class AXIS{
private:
	/********************
	基底ベクトルを正規直交空間の値で表現したもの.
	********************/
	ofVec3f e_x;
	ofVec3f e_y;
	ofVec3f e_z;
	
	ofVec3f center;
	
public:
	AXIS() : e_x(1, 0, 0), e_y(0, 1, 0), e_z(0, 0, 1), center(0, 0, 0){
	}
	
	void Reset()
	{
		e_x = ofVec3f(1, 0, 0);
		e_y = ofVec3f(0, 1, 0);
		e_z = ofVec3f(0, 0, 1);
		
		center = ofVec3f(0, 0, 0);
	}
	
	
	void translate(float x, float y, float z)
	{
		center += x * e_x;
		center += y * e_y;
		center += z * e_z;
	}
	
	/******************************
	URL
		Rotate quad made in geometry shader
			http://stackoverflow.com/questions/28124548/rotate-quad-made-in-geometry-shader
			
			shader上での実装も記述してあり、大変参考になる.
	******************************/
	void rotate(float angle_deg, ofVec3f _n)
	{
		/********************
		ofRotateと方向合わせる.
		********************/
		float angle_rad = -angle_deg * 3.1415 / 180.0;
		
		/********************
		_n は変換前の正規直交vector.
		e_xyzは、すでにmatrix変換されているかもしれないので、この、変換後の座標に直す。
		********************/
		ofVec3f n(0, 0, 0);
		n += e_x * _n.x;
		n += e_y * _n.y;
		n += e_z * _n.z;
		
		
		/********************
		********************/
		ofVec3f q;
		q.x =	  e_x.x * (n.x * n.x * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_x.y * (n.x * n.y * (1.0 - cos(angle_rad)) + n.z * sin(angle_rad))
				+ e_x.z * (n.x * n.z * (1.0 - cos(angle_rad)) - n.y * sin(angle_rad));
		
		q.y =   e_x.x * (n.y * n.x * (1.0 - cos(angle_rad)) - n.z * sin(angle_rad))
				+ e_x.y * (n.y * n.y * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_x.z * (n.y * n.z * (1.0 - cos(angle_rad)) + n.x * sin(angle_rad));
		
		q.z =   e_x.x * (n.z * n.x * (1.0 - cos(angle_rad)) + n.y * sin(angle_rad))
				+ e_x.y * (n.z * n.y * (1.0 - cos(angle_rad)) - n.x * sin(angle_rad))
				+ e_x.z * (n.z * n.z * (1.0 - cos(angle_rad)) + cos(angle_rad));
				
		e_x = q;
				
		/********************
		********************/
		q.x =	  e_y.x * (n.x * n.x * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_y.y * (n.x * n.y * (1.0 - cos(angle_rad)) + n.z * sin(angle_rad))
				+ e_y.z * (n.x * n.z * (1.0 - cos(angle_rad)) - n.y * sin(angle_rad));
		
		q.y =   e_y.x * (n.y * n.x * (1.0 - cos(angle_rad)) - n.z * sin(angle_rad))
				+ e_y.y * (n.y * n.y * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_y.z * (n.y * n.z * (1.0 - cos(angle_rad)) + n.x * sin(angle_rad));
		
		q.z =   e_y.x * (n.z * n.x * (1.0 - cos(angle_rad)) + n.y * sin(angle_rad))
				+ e_y.y * (n.z * n.y * (1.0 - cos(angle_rad)) - n.x * sin(angle_rad))
				+ e_y.z * (n.z * n.z * (1.0 - cos(angle_rad)) + cos(angle_rad));
				
		e_y = q;

		/********************
		********************/
		q.x =	  e_z.x * (n.x * n.x * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_z.y * (n.x * n.y * (1.0 - cos(angle_rad)) + n.z * sin(angle_rad))
				+ e_z.z * (n.x * n.z * (1.0 - cos(angle_rad)) - n.y * sin(angle_rad));
		
		q.y =   e_z.x * (n.y * n.x * (1.0 - cos(angle_rad)) - n.z * sin(angle_rad))
				+ e_z.y * (n.y * n.y * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_z.z * (n.y * n.z * (1.0 - cos(angle_rad)) + n.x * sin(angle_rad));
		
		q.z =   e_z.x * (n.z * n.x * (1.0 - cos(angle_rad)) + n.y * sin(angle_rad))
				+ e_z.y * (n.z * n.y * (1.0 - cos(angle_rad)) - n.x * sin(angle_rad))
				+ e_z.z * (n.z * n.z * (1.0 - cos(angle_rad)) + cos(angle_rad));
				
		e_z = q;
	}

	void scale(float x, float y, float z)
	{
		e_x *= x;
		e_y *= y;
		e_z *= z;
	}
	
	/******************************
	description
	
	param
		point
			変換後空間でのベクトル値.

		target
			return.
			正規直交空間上での座標.
	******************************/
	void get(ofVec3f point, ofVec3f& target)
	{
		target = center;
		
		target += point.x * e_x;
		target += point.y * e_y;
		target += point.z * e_z;
	}

};

/**************************************************
**************************************************/
class INDICATOR{
private:
	/****************************************
	enum
	****************************************/
	enum{
		NUM_PATTERNS = 8,
	};
	
	/****************************************
	param
	****************************************/
	/********************
	********************/
	int id_pattern;
	
	/********************
	********************/
    ofxPanel gui;
	ofxFloatSlider LineWidth;
    ofxIntSlider countX;
    ofxFloatSlider stepX;
    ofxFloatSlider twistX;
    
    ofxIntSlider countY;
    ofxFloatSlider stepY, twistY, pinchY;
	
    ofxGuiGroup globalGroup;
    ofxFloatSlider g_Scale;
    ofxFloatSlider g_Rotate;
    
    ofxGuiGroup primGroup;
    ofxFloatSlider primitive_shiftY, primitive_rotate;
    ofxVec2Slider primitive_size;
	ofxToggle b_PrimitiveSize_by_x;
    ofxColorSlider color;
    ofxToggle filled, type;
	
	ofxToggle MusicSync;
	ofxToggle b_SelfRotation;
    
    bool showGui;
	
	/****************************************
	****************************************/
	enum{
		/********************
		when countX = 200
		(countX * 2 + 1) * 4(頂点) = 1604.
		********************/
		NUM_VERTS = 4000,
	};

	ofVbo Vbo;
	ofVec3f vbo_Verts[NUM_VERTS];
	ofFloatColor vbo_Color[NUM_VERTS];

	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	INDICATOR();
	~INDICATOR();
	INDICATOR(const INDICATOR&); // Copy constructor. no define.
	INDICATOR& operator=(const INDICATOR&); // コピー代入演算子. no define.
	
	/********************
	********************/
	void stripePattern(double Dj_a);
    void matrixPattern(double Dj_a);
	
	void changeParam_MusicSync(vector<float>& spectrum);
	void SelfRotaion();

	void LoadXmlParameter();
	
public:
	/****************************************
	****************************************/
	static INDICATOR* getInstance(){
		static INDICATOR inst;
		return &inst;
	}
	
	
    void exit();
	
	void setup();
	void update(vector<float>& spectrum);
	void draw(double Dj_a);

	void keyPressed(int key);

	void RandomSet_Pattern();
	void set_color(COLORPATTERNS colorTheme);
};


