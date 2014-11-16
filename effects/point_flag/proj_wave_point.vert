// Copyright 2014 Lauri Gustafsson
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