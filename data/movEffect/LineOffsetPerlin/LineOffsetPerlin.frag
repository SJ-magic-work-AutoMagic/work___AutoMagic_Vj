/************************************************************
************************************************************/
#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect inputTexture;

#define num (256)
uniform float offset[num];

/******************************
ビルトイン関数(一部)
	http://qiita.com/edo_m18/items/71f6064f3355be7e4f45
******************************/
void main(){
	vec2 texCoord = gl_TexCoord[0].xy;
	
	int id = int(mod(texCoord.y, num));
	texCoord.x += offset[id];
	
	vec4 color = texture2DRect( inputTexture, texCoord );
	color.a = 1.0;
	
	gl_FragColor = color;
}
