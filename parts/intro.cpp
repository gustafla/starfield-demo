#include "parts/intro.hpp"

PIntro::PIntro(CommonData* icommon):
common(icommon) {
    metaballs = new GfxScreen(icommon, "shaders/metaballs.frag", "", 2.0);
    rb = new GfxPostProcessor(icommon, "shaders/rb_post.frag", GL_LINEAR, 2.0);
    mehutext = new GfxScreenMovable(icommon, "shaders/showtex_var.frag", icommon->res[0]/3, icommon->res[1]/6, icommon->res[0]/6, icommon->res[1]/6, "mehutext.tga");
    yeartext = new GfxScreenMovable(icommon, "shaders/showtex_var.frag", (icommon->res[0]/12)*7, (icommon->res[1]/6)*2, icommon->res[0]/6, icommon->res[1]/6, "yeartext.tga");
    revisiontext = new GfxScreenMovable(icommon, "shaders/showtex_var.frag", (icommon->res[0]/12)*2, (icommon->res[1]/6)*3, icommon->res[0]/6, icommon->res[1]/6, "revisiontext.tga");
}

PIntro::~PIntro() {
    delete metaballs;
    delete mehutext;
    delete revisiontext;
    delete yeartext;
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
    if (common->t > 15.7)
        mehutext->draw();
    if (common->t > 19.6)
        yeartext->draw();
    if (common->t > 23.45)
        revisiontext->draw();
}
