varying vec2 texpos;
uniform sampler2D iChannel0;

void main() {
    gl_FragColor = texture2D(iChannel0, texpos);
}
