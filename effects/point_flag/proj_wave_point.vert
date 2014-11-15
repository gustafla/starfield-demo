attribute vec4 vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 yRotation;
uniform mat4 xRotation;
uniform mat4 zRotation;
uniform vec2 iResolution;
uniform float beat;

void main() {
    vec4 v = vertex;
    v.z+=sin(4.0*v.x+v.y+iGlobalTime*2.0)*0.2;
    v.z+=cos(iGlobalTime+v.x*v.y*6.0)*0.05;
    v.z+=sin(10.0*sin(v.x+iGlobalTime)+iGlobalTime*0.2)*0.02;
    v *= xRotation*zRotation*yRotation;
    v.z -= sin(iGlobalTime)*0.4+2.0;
    v.y += ((beat)*0.2);
	gl_PointSize = (iResolution.x/16.0)*pow(clamp(((v.z/4.0)+1.0), 0.0, 1.0), 2.0);
    gl_Position = v * projection;
}
