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

//float BPS = 175.0/60.0;
//float PI  = 3.14159256;
float TIME  = 5.0;

void main() {
    vec4 v = vertex;
    v.z -= iGlobalTime;
    v.z = mod(v.z, 10.0);
    v.z -= 5.0;
	v *= yRotation * xRotation * zRotation;
    //v.y-=abs(sin((iGlobalTime*0.5)*PI*BPS)*0.2);
    //v.z-=pow(max(0.0,-(TIME*0.5-1.0)+(iGlobalTime-(TIME*0.5-1.0))),max(1.0,-(TIME*0.5-1.0)+(iGlobalTime-(TIME*0.5-1.0))));
    float perspective = clamp(((v.z/4.0)+1.0), 0.0, 1.0);
	gl_PointSize = (iResolution.x/20.0)*(perspective*perspective)*((1.0-beat)+0.4);
    gl_Position = v * projection;
}
