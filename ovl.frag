uniform vec2 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

float PI = 3.14159265;

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    vec2 wpos = vec2(pos.x, pos.y+sin(pos.x*4.0+iGlobalTime)*0.1);
    vec4 mehupic = texture2D(iChannel0, wpos);
    vec3 col = vec3(1.0, 0.0, 0.0);
    float sh = clamp((sin((pos.x+pos.y)*10.0+iGlobalTime*10.0)*20.0-19.0)*clamp(sin((pos.x+pos.y)+iGlobalTime)*10.0-9.0, 0.0, 1.0), 0.0, 1.0);
    col.gb += sh;
    gl_FragColor = vec4(col*mehupic.r, mehupic.a);

    float colT = mehupic.b;
    gl_FragColor.rgb += colT * vec3(sin(4.0*pos.x+iGlobalTime*2.0+(PI/3.0))*0.5+0.5, sin(4.0*pos.x+iGlobalTime*2.0+((PI/3.0)*2.0))*0.5+0.5, sin(4.0*pos.x+iGlobalTime*2.0+PI)*0.5+0.5);
}
