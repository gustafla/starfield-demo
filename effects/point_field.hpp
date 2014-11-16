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

#ifndef POINT_FIELD_HPP
#define POINT_FIELD_HPP

#include <vector>
#include "rpi_gfx.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_shader.hpp"
#include "common.hpp"

class PointField {
    public:
        PointField(CommonData* icommon, unsigned int const count=2000);
        ~PointField();
        void draw();
    private:
        CommonData* common;
        GfxShader shaderProgram;
        GfxTexture2D* pointTexture;
        std::vector<GLfloat> geometry;

        GLfloat pProjMat[16];
        GLfloat rotationMatrices[3][16];
        
        //GLuint vertexBuffer;
};

#endif