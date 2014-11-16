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

#include "gfx_mat.hpp"
#include <cmath>

void getPProjMat(float* mat, float fov, float aspect, float znear, float zfar) {
    float xymax = znear * tan(fov * (M_PI/360.0));
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = zfar - znear;
    float q = -(zfar + znear) / depth;
    float qn = -2 * (zfar * znear) / depth;

    float w = 2 * znear / width;
    w = w / aspect;
    float h = 2 * znear / height;

    mat[0] = w;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = h;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = q;
    mat[11] = -1.0;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = qn;
    mat[15] = 0.0f;
}

void getXRotMat(float* mat, float a) {
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = cos(a);
    mat[6] = -sin(a);
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = sin(a);
    mat[10] = cos(a);
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void getYRotMat(float* mat, float a) {
    mat[0] = cos(a);
    mat[1] = 0.0f;
    mat[2] = sin(a);
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = 1.0f;  
    mat[6] = 0.0f;   
    mat[7] = 0.0f;

    mat[8] = -sin(a);
    mat[9] = 0.0f;  
    mat[10] = cos(a);
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void getZRotMat(float* mat, float a) {
    mat[0] = cos(a);
    mat[1] = -sin(a);
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = sin(a);
    mat[5] = cos(a);
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

