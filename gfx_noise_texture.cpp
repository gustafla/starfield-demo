// Copyright 2014 Lauri Gustafsson
/*
This file is part of [DEMO NAME].

    [DEMO NAME] is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    [DEMO NAME] is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

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
