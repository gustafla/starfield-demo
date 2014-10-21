uniform vec2 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    pos.y += sin(pos.x*4.0+iGlobalTime)*0.1;
    gl_FragColor = texture2D(iChannel0, pos);
    gl_FragColor.a -= clamp(1.0-iGlobalTime, 0.0, 1.0);
}
