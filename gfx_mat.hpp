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

//Matrices will be just 1-dimensional arrays of float.

#ifndef GFX_MAT
#define GFX_MAT

void multMat4(float* result, float* a, float* b);
void getPProjMat(float* mat, float fov, float aspect, float znear=1.0, float zfar=10.0);
void getXRotMat(float* mat, float a);
void getYRotMat(float* mat, float a);
void getZRotMat(float* mat, float a);
void getTranslationMat(float* mat, float x, float y, float z);
void getScaleMat(float* mat, float x, float y, float z);
void getScaleMat(float* mat, float x);

#endif
