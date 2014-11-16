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

#ifndef GFX_POSTPROCESSOR_HPP
#define GFX_POSTPROCESSOR_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "common.hpp"
#include <string>

class GfxPostProcessor {
    public:
        GfxPostProcessor(CommonData* icommon, std::string vs, GfxTexture2D* iiChannel0=NULL, GfxTexture2D* iiChannel1=NULL, GLuint filter=GL_NEAREST, float c=1.0, float cy=0.0);
        ~GfxPostProcessor();
        void draw();
        void bindFramebuffer();
        GfxTexture2D* getTexture();
        void takei1(GfxTexture2D* i);
        void takei2(GfxTexture2D* i);
    private:
        CommonData* common;
        GfxShader shaderProgram;
        GfxTexture2D* iChannel0;
        GfxTexture2D* iChannel1;
        GfxTexture2D* iChannel2;
        GfxTexture2D* selfOut;
        GLfloat vertices[8];
        GLuint frameBuffer;
        GLuint renderBuffer;
};

#endif