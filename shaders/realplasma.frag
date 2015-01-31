uniform float iGlobalTime;
uniform float beat;
uniform vec2 iResolution;

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    pos.y += (sin(pos.y*6.0+iGlobalTime) + sin(pos.y*2.0-iGlobalTime*0.6)*0.3)*0.3;
    pos.x += (sin(pos.y*5.0+iGlobalTime*1.2)*0.7 + sin(pos.y*4.0-iGlobalTime*0.5)*0.4 + sin(pos.y*4.0+iGlobalTime*0.8))*0.3;
    float primaryMap = ((sin(pos.x*12.0+iGlobalTime*0.3)+0.5) + sin(pos.y*10.0+iGlobalTime) +
                        sin(pos.y*3.0*pos.x*2.0+iGlobalTime*1.3)*0.4+0.4 + sin(pos.x+pos.y+iGlobalTime*1.3)*2.0) * (cos(pos.y*pos.x*4.0+iGlobalTime)*0.8+1.2 + (sin(pos.x*2.0+iGlobalTime)*0.3+1.0));
    //primaryMap *= 0.1;
    primaryMap += beat*2.0+2.0;
    gl_FragColor = vec4(vec3(sin(primaryMap), sin(primaryMap+1.7), sin(primaryMap+3.66666)*0.3), 1.0);
}
