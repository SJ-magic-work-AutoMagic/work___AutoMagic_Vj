/************************************************************
Geometry shader input/output 指定
ジオメトリシェーダで使う組み込み変数＆関数
	http://miffysora.wikidot.com/geometry-shader
************************************************************/
#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

//Add this for using geometry shader
#extension GL_EXT_geometry_shader4 : enable

/************************************************************
************************************************************/
uniform float TextureSize_w = 1280;
uniform float TextureSize_h = 720;


/************************************************************
************************************************************/
/******************************
******************************/
void main() {
	/********************
	********************/
	vec3 p[4];
	for(int i = 0; i < 4; i++){
		p[i] = gl_PositionIn[i].xyz;
	}
	
	/********************
	0---2
	|   |
	1---3
	********************/
	// const int TextureImageSize = 100;
	vec4 t[4];
	t[0] = vec4(0, 0, 0, 1);
	t[1] = vec4(0, TextureSize_h, 0, 1);
	t[2] = vec4(TextureSize_w, 0, 0, 1);
	t[3] = vec4(TextureSize_w, TextureSize_h, 0, 1);
	
	/********************
	********************/
	// vec4 color = vec4(0.0, 1.0, 0.0, 1.0);
	for(int i = 0; i < 4; i++){
		gl_Position = gl_ModelViewProjectionMatrix * vec4(p[i], 1.0);
		
		gl_FrontColor = gl_FrontColorIn[i];
		gl_TexCoord[0] = t[i];
		
		EmitVertex();
	}
	
	EndPrimitive();
}


