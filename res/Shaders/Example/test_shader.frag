// frag
uniform vec3 iResolution;
varying vec2 v_texCoord;
varying float iTime;

vec3 Strand(in vec2 fragCoord, in vec3 color, in float hoffset, in float hscale, in float vscale, in float timescale)
{
    float glow = 0.06 * iResolution.y;
    float twopi = 6.28318530718;
    float curve = 1.0 - abs(fragCoord.y - (sin(mod(fragCoord.x * hscale / 100.0 / iResolution.x * 1000.0 + iTime * timescale + hoffset, twopi)) * iResolution.y * 0.25 * vscale + iResolution.y / 2.0));
    float i = clamp(curve, 0.0, 1.0);
    i += clamp((glow + curve) / glow, 0.0, 1.0) * 0.4 ;
    return i * color;
}

vec3 Muzzle(in vec2 fragCoord, in float timescale)
{
    float theta = atan(iResolution.y / 2.0 - fragCoord.y, iResolution.x - fragCoord.x + 0.13 * iResolution.x);
    float len = iResolution.y * (10.0 + sin(theta * 20.0 + float(int(iTime * 20.0)) * -35.0)) / 11.0;
    float d = max(-0.6, 1.0 - (sqrt(pow(abs(iResolution.x - fragCoord.x), 2.0) + pow(abs(iResolution.y / 2.0 - ((fragCoord.y - iResolution.y / 2.0) * 4.0 + iResolution.y / 2.0)), 2.0)) / len));
    return vec3(d * (1.0 + sin(theta * 10.0 + floor(iTime * 20.0) * 10.77) * 0.5), d * (1.0 + -cos(theta * 8.0 - floor(iTime * 20.0) * 8.77) * 0.5), d * (1.0 + -sin(theta * 6.0 - floor(iTime * 20.0) * 134.77) * 0.5));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    float timescale = 4.0;
    vec3 c = vec3(0, 0, 0);
    c += Strand(fragCoord, vec3(1.0, 0, 0), 0.7934 + 1.0 + sin(iTime) * 30.0, 1.0, 0.16, 10.0 * timescale);
    c += Strand(fragCoord, vec3(0.0, 1.0, 0.0), 0.645 + 1.0 + sin(iTime) * 30.0, 1.5, 0.2, 10.3 * timescale);

    c += clamp(Muzzle(fragCoord, timescale), 0.0, 1.0);
    fragColor = vec4(c.r, c.g, c.b, 1.0);
}


void mainImage2( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = -1.0 + 2.0*fragCoord.xy / iResolution.xy;
    uv.x *=  iResolution.x / iResolution.y;

    // background    
    vec3 color = vec3(0.8 + 0.2*uv.y);

    // bubbles  
    for( int i=0; i<40; i++ )
    {
        // bubble seeds
        float pha =      sin(float(i)*546.13+1.0)*0.5 + 0.5;
        float siz = pow( sin(float(i)*651.74+5.0)*0.5 + 0.5, 4.0 );
        float pox =      sin(float(i)*321.55+4.1) * iResolution.x / iResolution.y;

        // buble size, position and color
        float rad = 0.1 + 0.5*siz;
        vec2  pos = vec2( pox, -1.0-rad + (2.0+2.0*rad)*mod(pha+0.1*iTime*(0.2+0.8*siz),1.0));
        float dis = length( uv - pos );
        vec3  col = mix( vec3(0.94,0.3,0.0), vec3(0.1,0.4,0.8), 0.5+0.5*sin(float(i)*1.2+1.9));
        //    col+= 8.0*smoothstep( rad*0.95, rad, dis );
        
        // render
        float f = length(uv-pos)/rad;
        f = sqrt(clamp(1.0-f*f,0.0,1.0));
        color -= col.zyx *(1.0-smoothstep( rad*0.95, rad, dis )) * f;
    }

    // vigneting    
    color *= sqrt(1.5-0.5*length(uv));

    fragColor = vec4(color,1.0);
}

void main(void)
{
    vec2 fragCoord = v_texCoord;
    mainImage2(gl_FragColor.rgba, fragCoord); // gl_FragCoord.xy);
    //gl_FragColor += vec4(0.0,0,0,0.6);
}