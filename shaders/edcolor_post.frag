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
uniform vec2 iResolution;
uniform float iGlobalTime;
uniform sampler2D iChannel0;

void main() {
    const float step = 0.7;
    const float pi = 3.14159265;
    vec2 pos=gl_FragCoord.xy/iResolution.xy;
    vec2 oneoff = vec2(1.0)/iResolution.xy;
    float edcolor = 0.0;
    for (float i=0.0; i<2.0*pi; i+=step*pi) {
        edcolor += distance(texture2D(iChannel0, pos+oneoff*vec2(sin(i), cos(i))).rgb, texture2D(iChannel0, pos+oneoff*vec2(sin(i-step*1.141592), cos(i-0.6*1.141592))).rgb);
    }
    vec3 col = texture2D(iChannel0, pos).rgb;
    vec3 col2 = texture2D(iChannel0, pos+oneoff).rgb;
    vec3 col3 = texture2D(iChannel0, pos-oneoff).rgb;
    vec3 col4 = texture2D(iChannel0, vec2(pos.x+oneoff.x, pos.y-oneoff.y)).rgb;
    vec3 col5 = texture2D(iChannel0, vec2(pos.x-oneoff.x, pos.y+oneoff.y)).rgb;
    vec3 colmean = (col+col2+col3+col4+col5)/5.0; //This is done for smoother colors against a dark background
    gl_FragColor = vec4(col+edcolor*50.0*colmean, 1.0);
}
