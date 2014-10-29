uniform float iGlobalTime;
uniform vec2 iResolution;
uniform sampler2D iChannel0;

void main() {
    gl_FragColor = texture2D(iChannel0, vec2(gl_PointCoord.x, 1.0-gl_PointCoord.y));
    gl_FragColor.a -= (-0.8)+gl_FragCoord.z*2.0;
}
