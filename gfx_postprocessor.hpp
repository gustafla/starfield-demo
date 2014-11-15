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
