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
uniform sampler2D iChannel0;
uniform sampler2D iChannel1;
//uniform sampler2D iChannel2;

vec2 noiseSize = vec2(42.0);

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 pos=gl_FragCoord.xy/iResolution.xy;
    vec2 offpos=(gl_FragCoord.xy+3.0)/iResolution.xy;
    vec3 texCol = texture2D(iChannel0, pos).rgb;
    texCol.rgb -= mod(gl_FragCoord.y, 2.0)*1.-1.;
    vec3 blurCol = texture2D(iChannel1, offpos).rgb;
    gl_FragColor = vec4(mix(texCol, blurCol, 0.5)*1.1, 1.0);
    gl_FragColor.rgb += rand(pos+iGlobalTime*0.001)*0.1-0.05;
    //gl_FragColor.rgb += texture2D(iChannel2, gl_FragCoord.xy/noiseSize).rgb *0.2 -0.1;
}
