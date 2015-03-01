uniform float iGlobalTime;
uniform sampler2D iChannel0;
varying vec2 texpos;

void main() {
    //float mov = sin(texpos.x*40.0-iGlobalTime*2.0)*0.5+0.5;
    float alpha = texture2D(iChannel0, vec2(texpos.x, texpos.y/*(mov+1.0)-(mov*0.5)*/)).r;
    vec3 col = vec3(sin(texpos.x*20.0+iGlobalTime), sin(texpos.x*20.0+iGlobalTime*1.5), sin(texpos.x*20.0+iGlobalTime*0.5))*0.5+0.5;
    gl_FragColor = vec4(col, alpha);
}
