attribute vec3 vertex;
attribute vec3 a_texpos;
varying vec2 texpos;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 xRotation;
uniform mat4 yRotation;
uniform mat4 zRotation;

void main() {
    texpos = a_texpos.xy;
    vec4 vm = vec4(vertex, 1.0) * xRotation;
    vm *= yRotation;
    vm *= zRotation;
    vm = vec4(vm.xy, vm.z-4.0, vm.w);
    gl_Position = vm * projection;
}
