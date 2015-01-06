#include "parts/plasma_bars.hpp"

PPlasma::PPlasma(CommonData* icommon) {
    plasma = new GfxScreen(icommon, "shaders/plasma9001dubstep.frag");
}

PPlasma::~PPlasma() {
    delete plasma;
}

void PPlasma::draw() {
    plasma->draw();
}
