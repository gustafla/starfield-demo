uniform float iGlobalTime;
uniform float startTime;
uniform float minusTime;
uniform sampler2D iChannel0;
varying vec2 texpos;

void main() {
    float t = iGlobalTime-startTime-minusTime;
    vec2 pos = vec2(clamp(pos.x, 0.0, t), pos.y);
    gl_FragColor = texture2D(iChannel0, pos);
}
