varying vec2 pixpos;
uniform sampler2D iChannel0;

void main() {
    gl_FragColor = texture2D(iChannel0, pixpos);
}
