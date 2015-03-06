// Copyright 2015 Lauri Gustafsson
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

#include "texobj.hpp"
#include <cmath>

PTexobj::PTexobj(CommonData* icommon):
common(icommon) {
    texture = new GfxTexture2D("graphics/textest.tga");
    rgbt = new GfxTexture2D("graphics/rgbfilter.tga");
    shader = new GfxShader("shaders/dirlighttexturing.vert", "shaders/showtex_var_simpleshade.frag");
    shader->use();
    glUniform1i(shader->getUfmHandle("iChannel0"), 0);
    glUniformMatrix4fv(shader->getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat40);
    model = common->models->getModel("cube_tex.obj");
    getTranslationMat(translation, 0, 0, -8);
    getTranslationMat(view, -2, 0, 0);
    glUniformMatrix4fv(shader->getUfmHandle("translation"), 1, GL_FALSE, translation);
    glUniformMatrix4fv(shader->getUfmHandle("view"), 1, GL_FALSE, view);
    glUniform3f(shader->getUfmHandle("lightdir"), 0.0, 0.0, -1.0);
    rgb = new GfxPostProcessor(icommon, "shaders/rgbfilt.frag");
    rgb->takeTexture(rgbt, "rgbfilter");
}

PTexobj::~PTexobj() {
    delete shader;
    delete texture;
    common->models->freeModel("doublecube_nm.obj");
}

void PTexobj::draw(GfxPostProcessor* pp) {
    shader->use();
    getXRotMat(xr, common->t*0.2);
    getYRotMat(yr, common->t*0.8);
    getZRotMat(zr, common->t*0.6);

    glUniformMatrix4fv(shader->getUfmHandle("xRotation"), 1, GL_FALSE, xr);
    glUniformMatrix4fv(shader->getUfmHandle("yRotation"), 1, GL_FALSE, yr);
    glUniformMatrix4fv(shader->getUfmHandle("zRotation"), 1, GL_FALSE, zr);
    glUniform1f(shader->getUfmHandle("iGlobalTime"), common->t);
    texture->bindToUnit(0);
//    rgb->bindFramebuffer();
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    model->draw(shader);
//    pp->bindFramebuffer();
//    rgb->draw();
}
