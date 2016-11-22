/************************************************************
ビルトイン関数(一部)
	http://qiita.com/edo_m18/items/71f6064f3355be7e4f45
************************************************************/
#version 120
#extension GL_ARB_texture_rectangle: enable

/************************************************************
************************************************************/
uniform float Time;

uniform sampler2DRect inputTexture;

/************************************************************
************************************************************/

/******************************
******************************/
float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

/******************************
******************************/
void main(){
	/********************
	********************/
	vec2 texCoord = gl_TexCoord[0].xy;
	vec4 color = texture2DRect( inputTexture, vec2(texCoord.x, texCoord.y) );
	
	/********************
	Random number
	********************/
	vec2 pos = texCoord.xy;
	pos *= sin(Time);
	float r = rand(pos);
	
	/********************
	Noise color using random number.
	********************/
	vec3 noise = vec3(r);
	float noise_intensity = 0.5;
	
	/********************
	Combined colors.
	********************/
	color = vec4( mix(color.rgb, noise, noise_intensity), 1.0 );
	// color = vec4(color.rgb + noise, 1.0);
	
	gl_FragColor = color;
}



