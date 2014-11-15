uniform vec2 iResolution;
uniform sampler2D iChannel0;

float offset[5];
float weight[5];

void main() {
    offset[0] = 0.0;
    offset[1] = 1.0;
    offset[2] = 2.0;
    offset[3] = 3.0;
    offset[4] = 4.0;
    weight[0] = 0.2270270270;
    weight[1] = 0.1945945946;
    weight[2] = 0.1216216216;
    weight[3] = 0.0540540541;
    weight[4] = 0.0162162162;

    vec3 fragmentColor;

    fragmentColor = texture2D( iChannel0, gl_FragCoord.xy/iResolution.xy ).rgb * weight[0];
    for (int i=1; i<5; i++) {
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)+vec2(0.0, offset[i]) )/iResolution.xy ).rgb * weight[i];
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)-vec2(0.0, offset[i]) )/iResolution.xy ).rgb * weight[i];
    }
    for (int i=1; i<5; i++) {
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)+vec2(offset[i], 0.0) )/iResolution.xy ).rgb * weight[i];
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)-vec2(offset[i], 0.0) )/iResolution.xy ).rgb * weight[i];
    }

    gl_FragColor = vec4(fragmentColor, 1.0);
}
