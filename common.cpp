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

#include "common.hpp"
#include "gfx_mat.hpp"

CommonData::CommonData(unsigned int x, unsigned int y):
t(0.0f),
deltat(0.0f),
beatHalfSine(0.0f) {
    halfYRes[0] = res[0] = x;
    res[1] = y;
    halfYRes[1] = y/2;
    models = new GfxModelHandler;
    getPProjMat(pProjMat40, 40.0, ((float)x)/((float)y), 0.1, 100.0);
    getPProjMat(pProjMat80, 80.0, ((float)x)/((float)y), 0.1, 100.0);
}
