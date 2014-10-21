attribute vec4 vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 yRotation;
uniform mat4 xRotation;
uniform mat4 zRotation;
uniform vec2 iResolution;

//float BPS = 175.0/60.0;
//float PI  = 3.14159256;
float TIME  = 5.0;

void main() {
	vec4 v = vertex * yRotation * xRotation * zRotation;
	v.z-=sin(iGlobalTime*0.2)*3.0;
    //v.y-=abs(sin((iGlobalTime*0.5)*PI*BPS)*0.2);
    //v.z-=pow(max(0.0,-(TIME*0.5-1.0)+(iGlobalTime-(TIME*0.5-1.0))),max(1.0,-(TIME*0.5-1.0)+(iGlobalTime-(TIME*0.5-1.0))));
	gl_PointSize = (iResolution.x/200.0)*clamp(((v.z/2.0)+1.5), 0.0, 1.0);
    gl_Position = v * projection;
}
