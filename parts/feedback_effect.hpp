#include "rpi_gfx.hpp"
#include "gfx_postprocessor.hpp"
#include "gfx_screen_movable.hpp"
#include "gfx_screen.hpp"

class PFeedbackEffect {
    public:
        PFeedbackEffect(CommonData* _common);
        ~PFeedbackEffect();
        void draw(GfxPostProcessor* pp);
    private:
        CommonData* common;
};
