
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 textureSize;
uniform vec2 mosaicSize;

void main()
{
	vec2 curPoint = vec2(v_texCoord.x*textureSize.x,v_texCoord.y*textureSize.y);
	
	vec2 centerPoint = vec2(floor(curPoint.x/mosaicSize.x)* mosaicSize.x,floor(curPoint.y/mosaicSize.y)*mosaicSize.y)+0.5*mosaicSize;
	
	vec2 nvCenter = vec2(centerPoint.x/textureSize.x,centerPoint.y/textureSize.y);
	
	gl_FragColor = texture2D(CC_Texture0,nvCenter);
}
