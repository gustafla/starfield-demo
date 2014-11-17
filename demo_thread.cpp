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

#include "demo_thread.hpp"
#include "config.hpp"
#include "gfx_EGL_window.hpp"
#include <cstdlib>
#include "rpi_gfx.hpp"
#include "common.hpp"
#include <pthread.h>
#include "wav_player.hpp"
#include "audio_thread.hpp"
#include "gfx_postprocessor.hpp"
#include <cmath>
#include "gfx_noise_texture.hpp"
#include <iostream>
#include "parts/starfield.hpp"
#include "parts/flag.hpp"

#define BPS 132.0/60.0

/*
 * Demo player thread function
 */
void* playDemo(void* arg) {
    //Get parameters
    DemoArg* args = (DemoArg*)arg;
    int argc = args->argc;
    char** argv = args->argv;
    Config c(argc, argv);
    //Create a window
    GfxEGLWindow window(&c);
    if(!window.createWindow(GFX_WINDOW_RGB))
        exit(2);

    //Set the clear color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    //Enable depth testing (why isn't this on by default?)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

  //glEnable(GL_CULL_FACE);

    //Set a viewport
    glViewport(0, 0, c.w, c.h);

    check();

    //Initialize cstdlib random seed
    srand(609);

    //GfxNoiseTexture mainNoise(48, 48);

    //Common data. Will be important when there are many effects/scenes in different (their own) objects
    CommonData common(c.w, c.h);
    
    WavPlayer* music = NULL;
    if (c.audio) {
        pthread_t audioThread;
        music = new WavPlayer("music.wav");
        pthread_create(&audioThread, NULL, playMusic, (void*)music);
    }
    
    GfxPostProcessor crt(&common, "crt.frag");
    GfxPostProcessor blur(&common, "fastblur.frag", crt.getTexture(), NULL, GL_LINEAR, 4.0);
    crt.takei1(blur.getTexture());
    //crt.takei2(mainNoise.getTexture());

    DemoStarfield p0(&common);
	DemoFlag      p1(&common);
	unsigned int  part = 0;
	float  tPartStart  = 0.0;
	float  tLoopStart  = 0.0;

    //Timer stuff
    struct timeval tTmp;
    struct timeval startT;
    struct timezone tz;
    float fpsLastT = 0.0f;
    unsigned int frames = 0;
    float t=0.0;
    float tMusicEOF = -1.0;

    gettimeofday(&tTmp, &tz);
    gettimeofday(&startT, &tz);

    for (;;)
    {
        //Check() checks that our fragile GL isn't seeing anything wrong going on
        check();

        //Update timer for the frame
        gettimeofday(&tTmp, &tz);
        t = static_cast<float>(tTmp.tv_sec - startT.tv_sec + ((tTmp.tv_usec - startT.tv_usec) * 1e-6));
        common.t = t-tLoopStart;
        common.beatHalfSine = std::abs(sin(t*M_PI*BPS)); //Wow, conflicting defs of abs() in libs!
        //common.beatHalfSine = 0.2;
        //std::cout << common.beatHalfSine << std::endl;
        //std::cout << common.t << std::endl;
        //mainNoise.generate();

        crt.bindFramebuffer(); //drawing to the "root" PP
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        switch (part) {
			case 0:
				p0.draw();
				if (t-tLoopStart > tPartStart+10.0){
					part++;
					tPartStart = t-tLoopStart;
				}
				break;
			case 1:
				p1.draw();
				if (t-tLoopStart > tPartStart+10.0){
					part++;
					tPartStart = t-tLoopStart;
				}
				break;
			default:
				part = 0;
				tLoopStart = t;
				tPartStart = t-tLoopStart;
				break;
		}

        blur.draw(); //Self drawing PPs bind their FB automatically
        glClear(GL_DEPTH_BUFFER_BIT);
        gfxBindFB0(); //Now we'll be drawing to screen
        crt.draw();
        //What was just drawn will now get read by the screen driver
        window.swapBuffers();
        //For clarity, it's good to clear both frame- and renderbuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (music != NULL) {
            if (tMusicEOF == -1.0 && music->done()) {
                tMusicEOF = t;
            }
            
            if (tMusicEOF != -1.0 && t >= (tMusicEOF+5.0)) {
                if (c.loop) {
                    part = 0;
                    tLoopStart = t;
                    tPartStart = t-tLoopStart;
                    music->restart();
                    tMusicEOF = -1.0;
                }
                else
                    break;
            }
        }
            
        //FPS counter "magic"
        if (c.fpsCounter) {
            frames++;
            if (frames > c.fpsIn)
            {
                std::cout << "FPS=" << (c.fpsIn / (t - fpsLastT)) << std::endl;
                fpsLastT = t;
                frames = 0;
            }
        }
    }
    exit(0);
}
