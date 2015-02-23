// Copyright 2015 Lauri Gustafsson
/*
This file is part of [DEMO NAME].

    [DEMO NAME] is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    [DEMO NAME] is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

attribute vec3 a_vertex;
attribute vec3 a_texpos;
attribute vec3 a_normal;
attribute vec3 a_lightdir;
varying vec2 texpos;
varying float light;
uniform mat4 projection;
uniform float iGlobalTime;
uniform mat4 xRotation;
uniform mat4 yRotation;
uniform mat4 zRotation;
uniform mat4 translation;

void main() {
    texpos = a_texpos.xy;
    light = 0.1+max(dot(a_normal*xRotation*yRotation*zRotation, a_lightdir), 0.0);
    vec4 vm = vec4(a_vertex, 1.0) * xRotation;
    vm *= yRotation;
    vm *= zRotation;
    vm *= translation;
    gl_Position = vm * projection;
}
