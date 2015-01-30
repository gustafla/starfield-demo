uniform float iGlobalTime;
uniform vec2 iResolution;

float fillCircle(vec2 cPos, float r) {
    vec2 pos = gl_FragCoord.xy/iResolution.yy - vec2(0.5);
    pos.x -= ((iResolution.x-iResolution.y)/iResolution.y)/2.0;
    return pow(max(1.0 - length(pos - cPos), 0.0), r);
}

void main() {
    float pL = 0.0;
    float t = iGlobalTime;
    float te = t*0.42;

    pL += fillCircle(vec2(cos(t*0.015*te-0.28)*0.6, cos(t*0.014*te)*0.3), 7.0);
    pL += fillCircle(vec2(sin(t*0.012*te)*0.5, cos(t*0.017*te)*0.233), 6.0);
    pL += fillCircle(vec2(cos(t*0.0171*te+0.52)*0.4, sin(t*0.0144*te)*0.32), 7.0);
    pL += fillCircle(vec2(sin(t*0.0122*te-0.4)*0.6, sin(t*0.0164*te)*0.13), 8.0);
    //pL += fillCircle(vec2(cos(t*0.53)*0.47, sin(t)*0.724), 5.0);

    pL = clamp((pL-0.5)*t*t*t*0.001/*"sharpness"*/, 0.0, 1.0);
    gl_FragColor = vec4(pL, pL, pL, 1.0);
}
