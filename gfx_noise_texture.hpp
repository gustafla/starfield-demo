#ifndef GFX_NOISE_TEXTURE_HPP
#define GFX_NOISE_TEXTURE_HPP

#include "gfx_texture_2D.hpp"

class GfxNoiseTexture {
    public:
        GfxNoiseTexture(unsigned int w, unsigned int h);
        ~GfxNoiseTexture();
        GfxTexture2D* getTexture();
        void generate();

    private:
        unsigned int width;
        unsigned int height;
        GfxTexture2D* texture;
        unsigned char* image;
};

#endif
