#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 resolution;

// predefine var brightness
vec3 brightness = vec3(0.2126, 0.7152, 0.0722);
float rgb2gray(vec4 color) {
    return dot(color.rgb, brightness);
}
float pixel_operator(float dx, float dy) {
    return rgb2gray( texture2D(CC_Texture0, v_texCoord + vec2(dx,dy)) );
}

// computes the brightness value
//float rgb2gray(vec3 color ) {
//    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 *
//    color.b;
//}

// per-pixel operator operations
//float pixel_operator(float dx, float dy) {
//    return rgb2gray(texture2D(CC_Texture0, v_texCoord +
//                            vec2(dx,dy)).rgb);
//}

float sobel_filter()
{
    float dx = 1.0 / float(resolution.x);
    float dy = 1.0 / float(resolution.y);

    float s00 = pixel_operator(-dx, dy);
    float s10 = pixel_operator(-dx, 0.0);
    float s20 = pixel_operator(-dx, -dy);
    float s01 = pixel_operator(0.0, dy);
    float s21 = pixel_operator(0.0, -dy);
    float s02 = pixel_operator(dx, dy);    
    float s12 = pixel_operator(dx, 0.0);
    float s22 = pixel_operator(dx, -dy);
    float sx = s00 + 2.0 * s10 + s20 - (s02 + 2.0 * s12 + s22);
    float sy = s00 + 2.0 * s01 + s02 - (s20 + 2.0 * s21 + s22);
    float dist = sx * sx + sy * sy;

    return dist;
}

vec4 heatMap(float v, float vmin, float vmax){
    float dv;
    float r, g, b;
    if (v < vmin)
        v = vmin;
    if (v > vmax)
        v = vmax;
    dv = vmax - vmin;
    if (v == 0.0) {
        return vec4(0.0, 0.0, 0.0, 1.0);
    }
    if (v < (vmin + 0.25f * dv)) {
        r = 0.0f;
        g = 4.0f * (v - vmin) / dv;
    } else if (v < (vmin + 0.5f * dv)) {
        r = 0.0f;
        b = 1.0f + 4.0f * (vmin + 0.25f * dv - v) / dv;
    } else if (v < (vmin + 0.75f * dv)) {
        r = 4.0f * (v - vmin - 0.5f * dv) / dv;
        b = 0.0f;
    } else {
        g = 1.0f + 4.0f * (vmin + 0.75f * dv - v) / dv;
        b = 0.0f; }
    return vec4(r, g, b, 1.0);
}

void main(){
    //compute the results of Sobel filter
    float graylevel = sobel_filter();
//    o_Color = heatMap(graylevel, 0.1, 3.0);
//    o_Color = vec4(graylevel, graylevel, graylevel, 1.0);
    // process the right side of the image
    //if(v_texCoord.x > 0.5)
    //    gl_FragColor = heatMap(graylevel, 0.0, 3.0) + texture2D(CC_Texture0, v_texCoord);
    //else
        gl_FragColor = vec4(graylevel, graylevel, graylevel, 1.0) ;
        //+ texture2D(CC_Texture0, v_texCoord);
}
