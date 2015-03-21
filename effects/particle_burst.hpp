#ifndef PARTICLE_BURST_HPP
#define PARTICLE_BURST_HPP

#include "common.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_shader.hpp"
#include "particle.hpp"
#include <vector>

class ParticleBurst {
    public:
        ParticleBurst(CommonData* icommon, float x, float y, float z, unsigned int num);
        ~ParticleBurst();
        void draw();
    private:
        GfxTexture2D texture;
        GfxShader shaderProgram;
        
        unsigned int numParts;
        GLfloat* coords;
        std::vector<Particle> particles;
};

#endif
