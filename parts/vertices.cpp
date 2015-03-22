#include "parts/vertices.hpp"
#include <cmath>

PVertices::PVertices(CommonData* icommon):
common(icommon),
shaderProgram("shaders/mvptex.vert", "shaders/showtex_var.frag"),
texture("graphics/triangles.tga"),
mvp(common->pProjMat80, 0.0f, 0.0f, -3.0f)
{
    cube = common->models->getModel("cube_tex.obj");
    //cube->changeDrawmode(GL_POINTS);
    shaderProgram.use();
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
}

PVertices::~PVertices() {
    
}

void PVertices::draw() {
    shaderProgram.use();
    texture.bindToUnit(0);
    
    for (float x=-4.0f; x<5.0f; x+=0.9f) {
        for (float y=-4.0f; y<5.0f; y+=0.9f) {
            mvp.setModelTranslation(x, y, 0.0f);
            mvp.setModelScale(0.2+sin(x+common->t)*0.1);
            mvp.setModelRotation(common->t*0.2, y+common->t*0.4, common->t*0.5);
            mvp.buildModel();
            mvp.buildMVP();
            glUniformMatrix4fv(shaderProgram.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
            cube->draw(&shaderProgram);
        }
    }
}
