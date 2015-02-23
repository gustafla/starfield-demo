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

#include "parts/plasma_bars.hpp"

PPlasma::PPlasma(CommonData* icommon) {
    plasma = new GfxScreen(icommon, "shaders/realplasma.frag");
}

PPlasma::~PPlasma() {
    delete plasma;
}

void PPlasma::draw() {
    plasma->draw();
}
