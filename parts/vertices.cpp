#include "parts/vertices.hpp"
#include <cmath>
#include "util.hpp"

PVertices::PVertices(CommonData* icommon):
common(icommon),
shaderProgram("shaders/mvptex.vert", "shaders/showtex_var.frag"),
texture("graphics/triangles.tga"),
mvp(common->pProjMat40, 0.0f, 0.0f, -7.0f)
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
    //mvp.setView(0.0f, 0.0f, sin(common->t*0.6)*2.0-8.0f, sin(common->t)*2.0f, 0.0f, sin(common->t)*2.0f);
    for (float x=-4.0f; x<5.0f; x+=0.9f) {
        for (float y=-3.0f; y<3.3f; y+=0.9f) {
            mvp.setModelTranslation(x, y, 0.0f);
            mvp.setModelScale(0.2f+sin(x+common->t)*0.1f+common->beatHalfSine*0.02f);
            mvp.setModelRotation(common->t*0.2f, y+common->t*0.4f, common->t*0.5f);
            mvp.buildModel();
            mvp.buildMVP();
            glUniformMatrix4fv(shaderProgram.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
            cube->draw(&shaderProgram);
        }
    }
}
