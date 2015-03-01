uniform vec2 iResolution;
uniform sampler2D iChannel0;
uniform sampler2D rgbfilter;

void main() {
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    vec2 posf = gl_FragCoord.xy/6.0;
    gl_FragColor = vec4(texture2D(iChannel0, pos).rgb * texture2D(rgbfilter, posf).rgb, 1.0);
}
