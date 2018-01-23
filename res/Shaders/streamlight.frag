#ifdef GL_ES
precision mediump float;
#endif



uniform vec2 iResolution;           // viewport resolution (in pixels)
varying float     iTime;           // shader playback time (in seconds)


float a(vec2 uv)
{
    uv.y = abs(uv.y);
    vec4 ss = vec4(uv.xy, .11, .79) - uv.yxyy + vec4(1.5,-1.2,0,0);
    return min(min(min(ss.x,ss.w),-uv.x),max(ss.y,ss.z));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = (fragCoord - iResolution.xy*0.5) * 3. / iResolution.y,
	     sup = vec2(-.5, .866),
         supo = vec2(.866, .5);
    
    float s = max(a(uv),max(a(vec2(dot(uv,sup), dot(uv,supo))),a(vec2(-dot(uv.yx,supo), dot(uv.yx,sup)))));
    
    vec4 col = vec4(.13,.17,.22,1.) + smoothstep(0.0*1.8,.0,s)*0.7;

    float i = smoothstep(.8,1.,sin(iTime*4.5+uv.x+uv.y));
    col += i*clamp(vec4(1)*s*.9+.1*i,.0,1.);
    
    fragColor = clamp(col,.0,1.);
}

void main( void)
{
    vec2 fragCoord = gl_FragCoord.xy;
	mainImage(gl_FragColor, fragCoord);
}