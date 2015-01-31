#ifndef GFX_OBJECT_HPP
#define GFX_OBJECT_HPP

#include "obj_iobject.hpp"
#include "gfx_shader.hpp"
#include "rpi_gfx.hpp"

class GfxModel {
    public:
        GfxModel(std::string objFileName, float* igeometry=NULL, unsigned int size=0, GLuint idrawmode=GL_TRIANGLES);
        ~GfxModel();
        void draw(GfxShader* shaderProgram);
        void draw(GfxShader* shaderProgram, float start);
        void changeShader();
    private:
        GLuint drawmode;
        GLuint vbo;
        //GLuint indexBuffer;
        std::vector<float> geometry;
        unsigned int numVertices;
};

#endif
