#include "particle.hpp"

Particle::Particle(CommonData* icommon, float x, float y, float z, float dx, float dy, float dz, float ax, float ay, float az) {
    common = icommon;
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    dirs[0] = dx;
    dirs[1] = dy;
    dirs[2] = dz;
    accels[0] = ax;
    accels[1] = ay;
    accels[2] = az;
}

GLfloat* Particle::tick() {
    for (int i=0; i<3; i++)
        dirs[i] += accels[i]*common->deltat;
    for (int i=0; i<3; i++)
        coords[i] += dirs[i]*common->deltat;
    return coords;
}
