#include "gfx_postprocessor.hpp"
#include "util.hpp"
#include <string>

GfxPostProcessor::GfxPostProcessor(CommonData* icommon, std::string fs, GfxTexture2D* iiChannel0, GfxTexture2D* iiChannel1, GLuint filter, float c, float cy):
common(icommon),
iChannel0(iiChannel0),
iChannel1(iiChannel1),
iChannel2(NULL),
selfOut(NULL) {
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
    
    if (cy==0.0)
		cy = c;
    
    GLfloat res[2] = {
        common->res[0]/c,
        common->res[1]/cy
    };

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    check();

    if (iChannel0 == NULL)
        iChannel0 = new GfxTexture2D(NULL, res[0], res[1], 0, GL_RGB, filter);
    else
        selfOut = new GfxTexture2D(NULL, res[0], res[1], 0, GL_RGB, filter);
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    glUniform1i(shaderProgram.getUfmHandle("iChannel1"), 1);
    glUniform1i(shaderProgram.getUfmHandle("iChannel2"), 2);

    if (selfOut != NULL)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, selfOut->getHandle(), 0);
    else
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, iChannel0->getHandle(), 0);
    
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, res[0], res[1]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

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

GfxPostProcessor::~GfxPostProcessor() {
    if (selfOut != NULL)
        delete selfOut;
    else
        delete iChannel0;
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);
}

void GfxPostProcessor::draw() {
    if (selfOut != NULL)
        bindFramebuffer();
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    iChannel0->bindToUnit(0);
    if (iChannel1 != NULL)
        iChannel1->bindToUnit(1);
    if (iChannel2 != NULL)
        iChannel2->bindToUnit(2);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, &common->t);

    //YOU NEED TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("vertex"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("vertex"));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GfxPostProcessor::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

GfxTexture2D* GfxPostProcessor::getTexture() {
    if (selfOut == NULL)
        return iChannel0;
    else return selfOut;
}

void GfxPostProcessor::takei1(GfxTexture2D* i) {
    iChannel1 = i;
}

void GfxPostProcessor::takei2(GfxTexture2D* i) {
    iChannel2 = i;
}
