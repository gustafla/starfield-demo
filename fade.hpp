#ifndef FADE_HPP
#define FADE_HPP

#include "gfx_postprocessor.hpp"
#include "common.hpp"

enum FadeType {FADE_BLACK_IN, FADE_BLACK_OUT};

class Fade {
    public:
        Fade(CommonData* icommon, float time=1.0, FadeType type=FADE_BLACK_OUT);
        ~Fade();
        void draw();
        void bindFramebuffer();
    private:
        GfxPostProcessor* fader;
};

#endif
