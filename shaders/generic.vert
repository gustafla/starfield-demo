attribute vec4 vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 xRotation;
uniform mat4 yRotation;
uniform mat4 zRotation;

void main() {
    vec4 vm = vertex;/* * xRotation;
    vm *= yRotation;
    vm *= zRotation;*/
    vm = vec4(vm.xy, vm.z-(sin(iGlobalTime*0.3)*0.2+2.4), vm.w);
    gl_Position = vm * projection;
}
