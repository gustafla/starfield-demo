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

#include "parts/starfield.hpp"

PStarfield::PStarfield(CommonData* icommon) {
    stars = new EPointField(icommon);
    ovl = new GfxScreenMovable(icommon, "shaders/ovl_var.frag", (icommon->res[0]/2)-((icommon->res[1]*0.52083)/2), 0, (icommon->res[1]*0.52083), icommon->res[1], "mehuovl.tga");
}

PStarfield::~PStarfield() {
    delete stars;
    delete ovl;
}

void PStarfield::draw() {
    stars->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    ovl->draw();
}
