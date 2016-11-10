#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect texture0;
uniform sampler2DRect texture1;
uniform sampler2DRect texture2;

uniform float mov_a;
uniform float mov_a_0_12;
uniform float mov_a_1_2;
uniform float b_GeneratedImage_on;
uniform float b_Mix_mov12_add;

void main(){
	vec2 pos = gl_TexCoord[0].xy;
	
	vec4 color0 = texture2DRect(texture0, pos);
	vec4 color1 = texture2DRect(texture1, pos);
	vec4 color2 = texture2DRect(texture2, pos);
	
	vec4 color_12;
	if(b_Mix_mov12_add == 1)	color_12.rgb = color1.rgb + color2.rgb * mov_a_1_2;
	else						color_12.rgb = color1.rgb * (1 - mov_a_1_2) + color2.rgb * mov_a_1_2;
	
	vec4 color;
	color.rgb = color0.rgb * (1 - mov_a_0_12) + color_12.rgb * mov_a_0_12;
	color.a = mov_a;
	
	if(b_GeneratedImage_on == 1.0){
		float Lum = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
		
		color.r = Lum;
		color.g = Lum;
		color.b = Lum;
	}

	//Output of the shader
	gl_FragColor = color;
}
