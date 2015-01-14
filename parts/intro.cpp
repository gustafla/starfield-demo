#include "parts/intro.hpp"

PIntro::PIntro(CommonData* icommon) {
    metaballs = new GfxScreen(icommon, "shaders/metaballs.frag", "", 2.0);
    rb = new GfxPostProcessor(icommon, "shaders/rb_post.frag", GL_LINEAR, 2.0);
}

PIntro::~PIntro() {
    delete metaballs;
    delete rb;
}

void PIntro::draw(Fade* drawTo) {
    rb->bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    metaballs->draw();
    if (drawTo==NULL)
        gfxBindFB0();
    else
        drawTo->bindFramebuffer();
    rb->draw();
}
