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

#ifndef DEMO_TEXOBJ_ED_HPP
#define DEMO_TEXOBJ_ED_HPP

#include "common.hpp"
#include "gfx_shader.hpp"
#include "gfx_postprocessor.hpp"
#include "gfx_mat.hpp"
#include "gfx_model.hpp"
#include "gfx_texture_2D.hpp"
#include "rpi_gfx.hpp"

class PTexobjED{
	public:
		PTexobjED(CommonData* icommon);
		~PTexobjED();
		void draw(GfxPostProcessor* pp);
	private:
        GfxPostProcessor* edPost;
        GfxShader* shader;
        GfxModel* model;
        GfxTexture2D* texture;
        
        CommonData* common;
        
        GLfloat xr[16];
        GLfloat yr[16];
        GLfloat zr[16];
        GLfloat tmp[16];
        GLfloat view[16];
};

#endif
