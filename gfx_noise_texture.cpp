#include "gfx_noise_texture.hpp"
#include <cstdlib>

GfxNoiseTexture::GfxNoiseTexture(unsigned int w, unsigned int h) {
    width = w;
    height = h;

    image = (unsigned char*)malloc(width * height * 3);
    texture = new GfxTexture2D(image, width, height, 0);
    generate();
}

GfxNoiseTexture::~GfxNoiseTexture() {
    delete texture;
    delete image;
}

void GfxNoiseTexture::generate() {
    for (unsigned int i = 0; i < width*height*3; i++) {
        image[i] = rand();
    }
    texture->image2D(image, width, height);
}

GfxTexture2D* GfxNoiseTexture::getTexture() {
    return texture;
}
