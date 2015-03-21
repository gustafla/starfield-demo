#include "effects/particle_burst.hpp"
#include "util.hpp"

ParticleBurst::ParticleBurst(CommonData* icommon, float x, float y, float z, unsigned int num):
texture("graphics/pallo.tga"),
shaderProgram("effects/particle_burst/simplepoint.vert", "shaders/textured_point.frag"),
numParts(num) {
    for (unsigned int n=0; n<num; n++) {
        particles.push_back(Particle(icommon, x, y, z, randf()*0.2, randf()*0.2, randf()*0.2, 0.0f, -0.04, 0.0));
    }
    coords = new GLfloat[3*num];
    
    shaderProgram.use();
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, icommon->pProjMat80);
    glUniform1i(shaderProgram.getUfmHandle("pointTexture"), 0);
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, icommon->res);
}

ParticleBurst::~ParticleBurst() {
    delete coords;
}

void ParticleBurst::draw() {
    GLfloat* tmpcoord;
    for (unsigned int n=0; n<numParts; n++) {
        tmpcoord = particles[n].tick();
        coords[n*3] = tmpcoord[0];
        coords[n*3+1] = tmpcoord[1];
        coords[n*3+2] = tmpcoord[2];
    }
    
    shaderProgram.use();
    texture.bindToUnit(0);

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("a_vertex"), 3, GL_FLOAT, GL_FALSE, 0, coords);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("a_vertex"));

    glDrawArrays(GL_POINTS, 0, numParts);
}
