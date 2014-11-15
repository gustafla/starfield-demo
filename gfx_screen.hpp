#ifndef GFX_SCREEN_HPP
#define GFX_SCREEN_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "common.hpp"
#include <string>

class GfxScreen {
    public:
        GfxScreen(CommonData* icommon, std::string fs, std::string i0="");
        void draw();
    private:
        GfxTexture2D* i;
        unsigned short iCount;
        GfxShader shaderProgram;
        CommonData* common;
        GLfloat vertices[8];
};

#endif
