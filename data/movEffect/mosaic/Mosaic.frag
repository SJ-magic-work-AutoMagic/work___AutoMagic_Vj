/************************************************************
ビルトイン関数(一部)
	http://qiita.com/edo_m18/items/71f6064f3355be7e4f45
************************************************************/
#version 120
#extension GL_ARB_texture_rectangle: enable

/************************************************************
************************************************************/
uniform int MosaicSize = 15;

uniform sampler2DRect inputTexture;

/************************************************************
************************************************************/

/******************************
******************************/
void main(){
	vec2 texCoord = gl_TexCoord[0].xy;
	
	int SpaceSize = int(MosaicSize * 0.1 + 0.5);
	SpaceSize = int(max(float(SpaceSize), 2.0));
	
	float x = (int(texCoord.x) / MosaicSize) * MosaicSize;
	float y = (int(texCoord.y) / MosaicSize) * MosaicSize;
	
	vec4 color = texture2DRect( inputTexture, vec2(x, y) );
	color.a = 1.0;
	
	if( (mod(texCoord.x, MosaicSize) < SpaceSize) || (mod(texCoord.y, MosaicSize) < SpaceSize) ){
		color.rgb *= 0.25;
	}
	
	gl_FragColor = color;
}

