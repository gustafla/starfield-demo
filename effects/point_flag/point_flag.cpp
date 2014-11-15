#include "effects/point_flag.hpp"
#include <string>
#include <cmath>
#include "tga_file.hpp"
#include "gfx_mat.hpp"
#include "rpi_gfx.hpp"
#include "util.hpp"

PointFlag::PointFlag(CommonData* icommon):
common(icommon) {
    //Load, compile, enable shaders
    std::string* fsTemp = new std::string;
    std::string* vsTemp = new std::string;
    if (!loadFile("textured_point.frag", *fsTemp))
        exit(40);
    if (!loadFile("effects/point_flag/proj_wave_point.vert", *vsTemp))
        exit(41);
    if(shaderProgram.compProgram(*vsTemp, *fsTemp) == GL_FALSE)
        exit(1);
    delete fsTemp;
    delete vsTemp;
    
    glUseProgram(shaderProgram.getHandle());

    //Load, set up texture
    TGAFile* image;

    image = new TGAFile;
    image->load("mehu256.tga");
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
    
    //Generate point "mat"
    for (float x=-1.2; x<1.2; x+=0.14) {
        for(float y=-0.9; y<0.9; y+=0.14) {
            points.push_back(x);
            points.push_back(y);
            points.push_back(0.0);
        }   
    }
    
    //Create projection matrix
    getPProjMat(pProjMat, 40.0f, common->res[0]/common->res[1]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, pProjMat);
}

PointFlag::~PointFlag() {
    delete pointTexture;
}

void PointFlag::draw() {
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    pointTexture->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);
    glUniform1fv(shaderProgram.getUfmHandle("beat"), 1, &common->beatHalfSine);

    //Let's update rotation matrices
    getXRotMat(&rotationMatrices[0][0], sin(common->t*0.2)*0.2);
    getYRotMat(&rotationMatrices[1][0], sin(common->t*0.3)*0.8);
    getZRotMat(&rotationMatrices[2][0], sin(common->t)*0.1);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("xRotation"), 1, GL_FALSE, &rotationMatrices[0][0]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("yRotation"), 1, GL_FALSE, &rotationMatrices[1][0]);
    glUniformMatrix4fv(shaderProgram.getUfmHandle("zRotation"), 1, GL_FALSE, &rotationMatrices[2][0]);

    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("vertex"), 3, GL_FLOAT, GL_FALSE, 0, &points[0]);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("vertex"));

    glDrawArrays(GL_POINTS, 0, points.size()/3);
    //Most waving and perspective magic happens in the shaders
}
