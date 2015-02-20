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

#ifndef RPI_GFX_HPP
#define RPI_GFX_HPP

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <stdarg.h>
#include <sys/time.h>
#include "bcm_host.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"

#define INT2P(i) (static_cast<char*>(0) + (i))

//  GfxEGLWindow flag - RGB color buffer
#define GFX_WINDOW_RGB 0
//  GfxEGLWindow flag - ALPHA color buffer
#define GFX_WINDOW_ALPHA 1
//  GfxEGLWindow flag - depth buffer
#define GFX_WINDOW_DEPTH 2
//  GfxEGLWindow flag - stencil buffer
#define GFX_WINDOW_STENCIL 4
//  GfxEGLWindow flag - multi-sample buffer
#define GFX_WINDOW_MULTISAMPLE 8

void check(std::string err = "");
void gfxBindFB0();

#endif
