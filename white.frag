uniform float iGlobalTime;
uniform vec2 iResolution;

void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragColor -= (-0.8)+gl_FragCoord.z*2.0;
}
