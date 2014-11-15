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
