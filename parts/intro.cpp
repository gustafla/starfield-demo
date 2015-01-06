#include "parts/intro.hpp"

PIntro::PIntro(CommonData* icommon) {
    metaballs = new GfxScreen(icommon, "shaders/metaballs.frag");
}

PIntro::~PIntro() {
    delete metaballs;
}

void PIntro::draw() {
    metaballs->draw();
}
