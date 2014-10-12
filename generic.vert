attribute vec4 vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 yRotation;
uniform mat4 xRotation;
uniform mat4 zRotation;

void main() {
	vec4 pv = vertex;
	pv.z-=5.0;
	vec4 v = pv * yRotation * xRotation * zRotation;
	//v.z-=5.0;//sin(iGlobalTime*0.2)*3.0+8.0;
	gl_PointSize = 10.0+8.0*(4.0*(v.z/10.0));
    gl_Position = v * projection;
}
