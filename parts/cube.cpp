// Copyright 2014 Lauri Gustafsson
/*
This file is part of [DEMO NAME].

    [DEMO NAME] is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    [DEMO NAME] is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include "cube.hpp"

PCube::PCube(CommonData* icommon):
common(icommon) {
    shader = new GfxShader("shaders/cube.vert", "shaders/green.frag");
    shader->use();
    GLfloat pProjMat[16] = {0};
    getPProjMat(pProjMat, 40.0, ((float)common->res[0])/((float)common->res[1]));
    glUniformMatrix4fv(shader->getUfmHandle("projection"), 1, GL_FALSE, pProjMat);
    cubeModel = common->models->getModel("cube.obj");
}

PCube::~PCube() {
    delete shader;
    common->models->freeModel("cube.obj");
}

void PCube::draw() {
    shader->use();
    getXRotMat(xr, common->t*0.2);
    getYRotMat(yr, common->t*0.8);
    getZRotMat(zr, common->t*0.6);

    glUniformMatrix4fv(shader->getUfmHandle("xRotation"), 1, GL_FALSE, xr);
    glUniformMatrix4fv(shader->getUfmHandle("yRotation"), 1, GL_FALSE, yr);
    glUniformMatrix4fv(shader->getUfmHandle("zRotation"), 1, GL_FALSE, zr);
    glUniform1f(shader->getUfmHandle("iGlobalTime"), common->t);
    //gfxBindFB0();
    cubeModel->draw(shader);
}
