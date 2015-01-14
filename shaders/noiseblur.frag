uniform float iGlobalTime;
uniform vec2 iResolution;
uniform sampler2D frameIn;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    float pulse = 0.01;//max(sin(iGlobalTime)*0.1+0.06, 0.0);
    vec2 pos = gl_FragCoord.xy/iResolution.xy;
    float ang = rand(pos-vec2(0.5))*360.0;//rand(pos+bpos);//rand(pos+iGlobalTime)*360.0;
    //pos.x += rand(pos+iGlobalTime)*pulse*0.1-0.05*pulse;
    //pos.y += rand(pos+iGlobalTime*0.99)*pulse*0.1-0.05*pulse;
    pos += vec2(cos(ang), sin(ang))*pulse*rand(pos+iGlobalTime);//*noiTex;
    gl_FragColor = vec4(texture2D(frameIn, pos).rgb, 1.0);
}
