#include "gfx_screen.hpp"
#include "util.hpp"
#include "tga_file.hpp"
#include <string>

GfxScreen::GfxScreen(CommonData* icommon, std::string fs, std::string i0):
common(icommon),
iCount(0) {
    //Load, compile, enable shaders
    std::string* fsTemp = new std::string;
    std::string* vsTemp = new std::string;
    if (!loadFile(fs, *fsTemp))
        exit(40);
    if (!loadFile("simple.vert", *vsTemp))
        exit(41);
    if(shaderProgram.compProgram(*vsTemp, *fsTemp) == GL_FALSE)
        exit(1);
    delete fsTemp;
    delete vsTemp;
    glUseProgram(shaderProgram.getHandle());

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, common->res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    check();
    
    if (i0 != "") {
        TGAFile* image;
        image = new TGAFile;
        image->load(i0);
        i = new GfxTexture2D(image->getImage(), image->getWidth(), image->getHeight(), 0, ((image->getBpp() == 32) ? GL_RGBA : GL_RGB));
        delete image;
        glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
        iCount=1;
    }

    //Here's our screen rectangle
    vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] = -1.0f;
    vertices[3] = 1.0f;
    vertices[4] = 1.0f;
    vertices[5] = 1.0f;
    vertices[6] = 1.0f;
    vertices[7] = -1.0f;
}

void GfxScreen::draw() { 
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    if (iCount)
        i->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    //IT'S CRUCIAL TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("vertex"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("vertex"));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
