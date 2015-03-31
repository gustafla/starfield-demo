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

#ifndef DEMO_POINTMODEL_HPP
#define DEMO_POINTMODEL_HPP

#include "common.hpp"
#include "gfx_shader.hpp" 
#include "gfx_screen.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_model.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include "mvp.hpp"

class PPointModel{
	public:
		PPointModel(CommonData* icommon, std::string name);
		~PPointModel();
		void draw();
		void resetTimer();
	private:
        CommonData* common;
        GfxShader shaderProgram;
		//GfxScreen bg;
		//GfxScreenMovable frameUp;
		//GfxScreenMovable frameDown;
        GfxModel* model;
        GfxTexture2D pointTexture;
        //GfxModel cube;
        MVP mvp;
        float startT;
};

#endif
