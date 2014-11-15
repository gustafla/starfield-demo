#ifndef DEMO_STARFIELD_HPP
#define DEMO_STARFIELD_HPP

#include "common.hpp"
#include "gfx_screen.hpp"
#include "effects/point_field.hpp"
#include "rpi_gfx.hpp"

class DemoStarfield {
    public:
        DemoStarfield(CommonData* icommon);
        ~DemoStarfield();
        void draw();
    private:
        //CommonData* common;
        PointField* stars;
        GfxScreen*  ovl;
};

#endif
