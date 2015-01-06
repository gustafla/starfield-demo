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

uniform float iGlobalTime;
uniform vec2 iResolution;
uniform sampler2D pointTexture;

void main() {
	//"Alpha test" :D
	vec4 color = texture2D(pointTexture, vec2(gl_PointCoord.x, 1.0-gl_PointCoord.y));
	if (color.a < 0.1)
		discard;
    gl_FragColor = color;
}
