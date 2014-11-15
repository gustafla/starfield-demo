#include "parts/starfield.hpp"

DemoStarfield::DemoStarfield(CommonData* icommon) {
    stars = new PointField(icommon);
    ovl = new GfxScreen(icommon, "ovl.frag", "mehuovl.tga");
}

DemoStarfield::~DemoStarfield() {
    delete stars;
    delete ovl;
}

void DemoStarfield::draw() {
    stars->draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    ovl->draw();
}
