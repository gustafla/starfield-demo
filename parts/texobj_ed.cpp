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

#include "texobj_ed.hpp"
#include <cmath>

PTexobjED::PTexobjED(CommonData* icommon):
common(icommon) {
    texture = new GfxTexture2D("textest.tga");
    shader = new GfxShader("shaders/texturedthing.vert", "shaders/showtex_var.frag");
    shader->use();
    glUniform1i(shader->getUfmHandle("iChannel0"), 0);
    glUniformMatrix4fv(shader->getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat40);
    model = common->models->getModel("doublecube.obj");
    edPost = new GfxPostProcessor(common, "shaders/edcolor_post.frag");
}

PTexobjED::~PTexobjED() {
    delete shader;
    delete texture;
    delete edPost;
    common->models->freeModel("biggerthing.obj");
}

void PTexobjED::draw(GfxPostProcessor* pp) {
    edPost->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    shader->use();
    getXRotMat(xr, common->t*0.2);
    getYRotMat(yr, common->t*0.8);
    getZRotMat(zr, common->t*0.6);

    glUniformMatrix4fv(shader->getUfmHandle("xRotation"), 1, GL_FALSE, xr);
    glUniformMatrix4fv(shader->getUfmHandle("yRotation"), 1, GL_FALSE, yr);
    glUniformMatrix4fv(shader->getUfmHandle("zRotation"), 1, GL_FALSE, zr);
    glUniform1f(shader->getUfmHandle("iGlobalTime"), common->t);
    texture->bindToUnit(0);
    //gfxBindFB0();
    model->draw(shader);
    pp->bindFramebuffer();
    edPost->draw();
}
