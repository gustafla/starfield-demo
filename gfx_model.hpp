#ifndef GFX_OBJECT_HPP
#define GFX_OBJECT_HPP

#include "obj_iobject.hpp"
#include "gfx_shader.hpp"
#include "rpi_gfx.hpp"

class GfxModel {
    public:
        GfxModel(std::string objFileName);
        ~GfxModel();
        void draw(GfxShader* shaderProgram);
        void changeShader();
    private:
        GLuint vbo;
        //GLuint indexBuffer;
        std::vector<float> geometry;
        unsigned int numVertices;
};

#endif
