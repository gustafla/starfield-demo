uniform vec2 iResolution;
uniform sampler2D iChannel0;

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    gl_FragColor = vec4(texture2D(iChannel0, pos).rgb, 1.0);
}
