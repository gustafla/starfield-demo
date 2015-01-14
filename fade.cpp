#include "fade.hpp"

Fade::Fade(CommonData* icommon, float s, FadeType type) {
    if (type == FADE_BLACK_OUT)
        fader = new GfxPostProcessor(icommon, "shaders/fadetoblack_post.frag", GL_LINEAR);
    else if (type == FADE_BLACK_IN)
        fader = new GfxPostProcessor(icommon, "shaders/fadefromblack_post.frag", GL_LINEAR);
    glUseProgram(fader->getShader()->getHandle());
    glUniform1f(fader->getShader()->getUfmHandle("tmult"), (1.0/s));
    glUniform1f(fader->getShader()->getUfmHandle("tstart"), icommon->t);
}

Fade::~Fade() {
    delete fader;
}

void Fade::draw() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fader->draw();
}

void Fade::bindFramebuffer() {
    fader->bindFramebuffer();
}
