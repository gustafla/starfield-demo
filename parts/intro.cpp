#include "parts/intro.hpp"

PIntro::PIntro(CommonData* icommon) {
    metaballs = new GfxScreen(icommon, "shaders/metaballs.frag");
    rb = new GfxPostProcessor(icommon, "shaders/rb_post.frag", GL_LINEAR);
}

PIntro::~PIntro() {
    delete metaballs;
    delete rb;
}

void PIntro::draw() {
    rb->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT);
    metaballs->draw();
    gfxBindFB0();
    rb->draw();
}
