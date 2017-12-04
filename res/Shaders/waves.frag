// frag
uniform vec2 iResolution;
varying vec2 v_texCoord;
varying float iTime;


vec2 center = vec2(0.5,0.5);
float speed = 0.035;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    float invAr = iResolution.y / iResolution.x;

    vec2 uv = fragCoord.xy / iResolution.xy;
        
    vec3 col = vec4(uv,0.5+0.5*sin(iTime),1.0).xyz;
   
     vec3 texcol;
            
    float x = (center.x-uv.x);
    float y = (center.y-uv.y) *invAr;
        
    //float r = -sqrt(x*x + y*y); //uncoment this line to symmetric ripples
    float r = -(x*x + y*y);
    float z = 1.0 + 0.5*sin((r+iTime*speed)/0.013);
    
    texcol.x = z;
    texcol.y = z;
    texcol.z = z;
    
    fragColor = vec4(col*texcol,1.0);
}

void main(void)
{
    vec2 fragCoord = gl_FragCoord.xy;
    mainImage(gl_FragColor.rgba, fragCoord); 
}