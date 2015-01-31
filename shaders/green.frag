uniform float iGlobalTime;
uniform vec2 iResolution;

/*void main() {
    vec2 uv = gl_FragCoord.xy/iResolution.xy;
    uv *= sin(iGlobalTime)*4.0+10.0;
    vec3 c = vec3(sin(uv.x)*sin(uv.y)*0.2+0.8);
    c.r*=0.5; c.b*=1.5;
    c-=gl_FragCoord.z*1.3;
    gl_FragColor = vec4(c, 1.0);
}*/

void main() {
    gl_FragColor=vec4(0.0, 1.0-max(gl_FragCoord.z*1.3-0.1, 0.0), 0.0, 1.0);
    //gl_FragColor=vec4(0.0, 1.0, 0.0, 1.0);
}
