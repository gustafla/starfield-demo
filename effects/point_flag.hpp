#ifndef POINT_FLAG_HPP
#define POINT_FLAG_HPP

#include <vector>
#include "gfx_texture_2D.hpp"
#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "common.hpp"

class PointFlag {
    public:
        PointFlag(CommonData* icommon);
        ~PointFlag();
        void draw();
    private:
        CommonData* common;
        std::vector<GLfloat> points;
        GfxTexture2D* pointTexture;
        GfxShader shaderProgram;

        float pProjMat[16];
        float rotationMatrices[3][16];
};

#endif
