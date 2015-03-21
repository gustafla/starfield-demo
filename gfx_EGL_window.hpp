// Copyright 2015 Lauri Gustafsson
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

#ifndef GFX_EGL_WINDOW_HPP
#define GFX_EGL_WINDOW_HPP

#include "config.hpp"
#include "rpi_gfx.hpp"
#include <string>

/*typedef enum {
    DISPMANX_FLAGS_ALPHA_FROM_SOURCE = 0,
    DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS = 1,
    DISPMANX_FLAGS_ALPHA_FIXED_NON_ZERO = 2,
    DISPMANX_FLAGS_ALPHA_FIXED_EXCEED_0X07 = 3,
    DISPMANX_FLAGS_ALPHA_PREMULT = 1 << 16,
    DISPMANX_FLAGS_ALPHA_MIX = 1 << 17
} DISPMANX_FLAGS_ALPHA_T;*/

class GfxEGLWindow
{
public:
    GfxEGLWindow(Config* ic);
    void swapBuffers();
    bool createWindow(GLuint flags);

protected:

    Config* c;
    EGLNativeWindowType window;
    EGLDisplay display;
    EGLContext context;
    EGLSurface buffer;
};

#endif
