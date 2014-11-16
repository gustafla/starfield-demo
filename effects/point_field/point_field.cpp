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

#include "effects/point_field.hpp"
#include "util.hpp"
#include "tga_file.hpp"
#include "gfx_mat.hpp"
#include <cmath>

PointField::PointField(CommonData* icommon, unsigned int const count):
common(icommon) {
    std::string* fsTemp = new std::string;
    std::string* vsTemp = new std::string;
    if (!loadFile("textured_point.frag", *fsTemp))
        exit(40);
    if (!loadFile("effects/point_field/star.vert", *vsTemp))
        exit(41);
    if(shaderProgram.compProgram(*vsTemp, *fsTemp) == GL_FALSE)
        exit(1);
    delete fsTemp;
    delete vsTemp;
    glUseProgram(shaderProgram.getHandle());

    //Load, set up texture
    TGAFile* image;
    image = new TGAFile;
    image->load("star.tga");
    pointTexture = new GfxTexture2D(image->getImage(), image->getWidth(), image->getHeight(), 0, ((image->getBpp() == 32) ? GL_RGBA : GL_RGB));
    pointTexture->bindToUnit(0);
    delete image;
    glUniform1i(shaderProgram.getUfmHandle("pointTexture"), 0);

    //Set miscellanous shader uniforms
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, common->res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("xRotation"), 1, GL_FALSE, &rotationMatrices[0][0]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("yRotation"), 1, GL_FALSE, &rotationMatrices[1][0]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("zRotation"), 1, GL_FALSE, &rotationMatrices[2][0]);

    check();

    //Create the random "starfield"
    for (int create_i = 0; create_i < count; create_i++) {
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
	}
    
    //Create projection matrix
    getPProjMat(pProjMat, 40.0f, common->res[0]/common->res[1]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, pProjMat);
}

PointField::~PointField() {
    delete pointTexture;
}

void PointField::draw() { 
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    pointTexture->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    //Let's update rotation matrices
    getXRotMat(&rotationMatrices[0][0], common->t*0.16);
    getYRotMat(&rotationMatrices[1][0], (common->t+sin(common->t*0.2))*0.1);
    getZRotMat(&rotationMatrices[2][0], common->t*0.12);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("xRotation"), 1, GL_FALSE, &rotationMatrices[0][0]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("yRotation"), 1, GL_FALSE, &rotationMatrices[1][0]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("zRotation"), 1, GL_FALSE, &rotationMatrices[2][0]);

    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("vertex"), 3, GL_FLOAT, GL_FALSE, 0, &geometry[0]);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("vertex"));

    glDrawArrays(GL_POINTS, 0, geometry.size()/3);
    //Most waving and perspective magic happens in the shaders
}
