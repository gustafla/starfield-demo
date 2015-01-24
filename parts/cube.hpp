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

#ifndef DEMO_CUBE_HPP
#define DEMO_CUBE_HPP

#include "common.hpp"
#include "gfx_shader.hpp"
#include "gfx_mat.hpp"
#include "gfx_model.hpp"
#include "rpi_gfx.hpp"

class PCube{
	public:
		PCube(CommonData* icommon);
		~PCube();
		void draw();
	private:
        GfxShader* shader;
        
        CommonData* common;
        
        GLfloat xr[16];
        GLfloat yr[16];
        GLfloat zr[16];
};

#endif
