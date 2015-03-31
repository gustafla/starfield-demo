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

#include "parts/pointmodel.hpp"
#include <cmath>
#include "util.hpp"

PPointModel::PPointModel(CommonData* icommon, std::string name):
common(icommon),
startT(-1.0f),
shaderProgram("shaders/points.vert", "shaders/textured_point.frag"),
pointTexture("graphics/mehu64.tga"),
mvp(NULL, 0.0f, 0.0f, -5.0f)/*
bg(icommon, "shaders/showtex.frag", "graphics/bg1.tga"),
frameUp(icommon, "shaders/showtex_var.frag", 0, 0, icommon->res[0], icommon->res[1]/12.0f, "graphics/frame_1_up.tga"),
frameDown(icommon, "shaders/showtex_var.frag", 0, (icommon->res[1]/12.0f)*11.0f, icommon->res[0], icommon->res[1]/12.0f, "graphics/frame_1_down.tga") */{
    model = common->models->getModel(name);
    model->changeDrawmode(GL_POINTS); //Duplicate points because face defs, I know. What you gonna do about it, I'm in a hurry! :D
    //cube->changeDrawmode(GL_POINTS);
    shaderProgram.use();
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, common->res);
}

PPointModel::~PPointModel() {
    
}

void PPointModel::draw() {
    if (startT<0.0f)
        startT = common->t;
        
    //bg.draw();
    //glClear(GL_DEPTH_BUFFER_BIT);
    shaderProgram.use();
    pointTexture.bindToUnit(0);
    
    mvp.setModelRotation(common->t*0.5f, common->t*0.4f, common->t*0.6f);
    mvp.setModelTranslation(0.0, common->beatHalfSine*0.2, sin(common->t)*0.7);
    mvp.buildModel();
    //mvp.buildMVP();
    glUniformMatrix4fv(shaderProgram.getUfmHandle("model"), 1, GL_FALSE, mvp.getModel());
    glUniformMatrix4fv(shaderProgram.getUfmHandle("view"), 1, GL_FALSE, mvp.getView());
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, common->pProjMat40);
    float drawT;
    if(1.0f>(drawT = 1.4f-(common->t/1.0f-startT/1.0f)))
        model->draw(&shaderProgram, drawT);
    //mvp.setView(0.0f, 0.0f, sin(common->t*0.6)*2.0-8.0f, sin(common->t)*2.0f, 0.0f, sin(common->t)*2.0f);
    /*for (float x=-4.0f; x<5.0f; x+=0.9f) {
        for (float y=-3.0f; y<3.3f; y+=0.9f) {
            mvp.setModelTranslation(x, y, 0.0f);
            mvp.setModelScale(0.2f+sin(x+common->t)*0.1f+(common->beatHalfSine*0.02f));
            mvp.setModelRotation(common->t*0.2f, y+common->t*0.4f, common->t*0.5f);
            mvp.buildModel();
            mvp.buildMVP();
            glUniformMatrix4fv(shaderProgram.getUfmHandle("mvp"), 1, GL_FALSE, mvp.mvp);
            cube->draw(&shaderProgram);
        }
    }*/
    //glClear(GL_DEPTH_BUFFER_BIT);
    //frameUp.draw();
    //frameDown.draw();
}

void PPointModel::resetTimer() {
    startT = -1.0f;
    model->changeDrawmode();
}
