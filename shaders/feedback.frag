uniform sampler2D iChannel0;
uniform float iGlobalTime;
uniform vec2 iResolution;

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    pos.x += sin(pos.y*8.0+iGlobalTime*0.5)*0.02;
    pos /= iGlobalTime*0.1+1.0;
    gl_FragColor = vec4(texture2D(iChannel0, pos).rgb, 1.0);
}
