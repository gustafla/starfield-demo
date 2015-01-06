#ifndef PLASMA_BARS_HPP
#define PLASMA_BARS_HPP

#include "common.hpp"
#include "gfx_screen.hpp"

class PPlasma {
    public:
        PPlasma(CommonData* icommon);
        ~PPlasma();
        void draw();
    private:
        GfxScreen* plasma;
};

#endif
