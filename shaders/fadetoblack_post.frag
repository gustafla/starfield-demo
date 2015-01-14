uniform sampler2D iChannel0;
uniform vec2 iResolution;
uniform float iGlobalTime;
uniform float tmult;
uniform float tstart;

void main() {
    float t=iGlobalTime-tstart;
    float tstretch=t*tmult;
    gl_FragColor = vec4(texture2D(iChannel0, gl_FragCoord.xy/iResolution.xy).rgb*(1.0-tstretch), 1.0);
    //gl_FragColor = vec4(1.0,0.5,0.0, 1.0); //Test :D
}
