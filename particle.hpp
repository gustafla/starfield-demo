#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "common.hpp"

class Particle {
    public:
        Particle(CommonData* icommon, float x, float y, float z, float dx, float dy, float dz, float ax, float ay, float az);
        GLfloat* tick();
    private:
        CommonData* common;
        GLfloat coords[3];
        GLfloat dirs[3];
        GLfloat accels[3];
};

#endif
