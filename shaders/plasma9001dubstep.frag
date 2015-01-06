uniform vec2 iResolution;
uniform float iGlobalTime;

const float PI = 3.14159265;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    pos+=vec2(sin(pos.x*4.0)*abs(sin(iGlobalTime*1.7*PI))*sin(pos.y), sin(pos.y*13.0+iGlobalTime))*0.1;
    pos.x+=sin(pos.y*7.0)*0.5;
    vec2 center = vec2(sin(iGlobalTime*0.3), cos(iGlobalTime+sin(iGlobalTime*1.2)))*0.3+1.2;
    
    vec3 primaryColor = vec3(0.0, 1.0, 0.1);
    
    float roundMap = sin(length(pos-center)*20.0)*4.0-3.0;
    
    gl_FragColor = vec4(primaryColor*roundMap, 1.0);
}
