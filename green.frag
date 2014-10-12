uniform float iGlobalTime;
uniform vec2 iResolution;

void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    //gl_FragColor.rgb -= gl_FragCoord.z*3.0;
    //gl_FragColor.rgb += 1.0;
}
