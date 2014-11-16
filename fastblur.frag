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

uniform vec2 iResolution;
uniform sampler2D iChannel0;

float offset[5];
float weight[5];

void main() {
    offset[0] = 0.0;
    offset[1] = 1.0;
    offset[2] = 2.0;
    offset[3] = 3.0;
    offset[4] = 4.0;
    weight[0] = 0.2270270270;
    weight[1] = 0.1945945946;
    weight[2] = 0.1216216216;
    weight[3] = 0.0540540541;
    weight[4] = 0.0162162162;

    vec3 fragmentColor;

    fragmentColor = texture2D( iChannel0, gl_FragCoord.xy/iResolution.xy ).rgb * weight[0];
    for (int i=1; i<5; i++) {
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)+vec2(0.0, offset[i]) )/iResolution.xy ).rgb * weight[i];
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)-vec2(0.0, offset[i]) )/iResolution.xy ).rgb * weight[i];
    }
    for (int i=1; i<5; i++) {
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)+vec2(offset[i], 0.0) )/iResolution.xy ).rgb * weight[i];
        fragmentColor += texture2D( iChannel0, ( vec2(gl_FragCoord)-vec2(offset[i], 0.0) )/iResolution.xy ).rgb * weight[i];
    }

    gl_FragColor = vec4(fragmentColor, 1.0);
}
