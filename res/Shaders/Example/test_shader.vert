attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;
varying float iTime;

void main()
{
    // use CC_PMatrix not CC_MVPMatrix for 2D Sprites
    gl_Position = CC_PMatrix * a_position;
    v_texCoord = a_texCoord;
    iTime = CC_Time[1];
}