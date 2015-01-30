attribute vec3 vertex;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 xRotation;
uniform mat4 yRotation;
uniform mat4 zRotation;

void main() {
    vec4 vm = vec4(vertex, 1.0) * xRotation;
    vm *= yRotation;
    vm *= zRotation;
    vm = vec4(vm.xy, vm.z-(sin(iGlobalTime)*2.0+4.0), vm.w);
    gl_Position = vm * projection;
    //gl_Position = vec4(vertex, 1.0);
}
