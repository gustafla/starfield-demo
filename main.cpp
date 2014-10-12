// Copyright 2014 Lauri Gustafsson
/*
This file is part of esfragt.

    esfragt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    esfragt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with esfragt, see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gfx_iobject.hpp"
#include "tga_file.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "rpi_gfx.hpp"
#include "gfx_EGL_window.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "util.hpp"
#include "config.hpp"
#include "text.hpp"
#include "gfx_mat.hpp"
#include <cmath>
#include <vector>

/*     (some :D) ERROR CODES:
 *
 *  1 - Shader program failed to compile/link
 *  2 - Failed to create window
 */

using namespace std;

int main(int argc, char *argv[])
{
    Config c(argc, argv);
    GfxEGLWindow window(&c);
    if(!window.createWindow(GFX_WINDOW_RGB))
        exit(2);

    std::string* fsTemp = new std::string;
    std::string* vsTemp = new std::string;
    if (false)
        *fsTemp = UNIFORMS;
    if (!loadFile("green.frag", *fsTemp))
        exit(40);
    if (!loadFile("generic.vert", *vsTemp))
        exit(41);
    GfxShader shaderProgram;
    if(shaderProgram.compProgram(*vsTemp, *fsTemp) == GL_FALSE)
        exit(1);
    delete fsTemp;

    glReleaseShaderCompiler();
    glUseProgram(shaderProgram.getHandle());

    TGAFile* image;
    for (unsigned short counter = 0; counter < c.imgs; counter++)
    {
        std::cout << "Image " << counter << ": " << c.inames[counter] << std::endl;
        image = new TGAFile;
        image->load(c.inames[counter]);
        glActiveTexture(GL_TEXTURE0+counter);
        gfxLoadTexture2D(image->getImage(), image->getWidth(), image->getHeight(), ((image->getBpp() == 32) ? GL_RGBA : GL_RGB));
        delete image;
    }
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    glUniform1i(shaderProgram.getUfmHandle("iChannel1"), 1);
    glUniform1i(shaderProgram.getUfmHandle("iChannel2"), 2);
    glUniform1i(shaderProgram.getUfmHandle("iChannel3"), 3);

    check();

    glEnable(GL_BLEND);
    if (!c.devmode)
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    else
        glBlendFunc(GL_ONE, GL_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    glViewport(0, 0, c.w, c.h);

    check();

    srand(time(NULL));

    std::vector<float> geometry;
    unsigned int const STARCOUNT = 10000;
    
    for (int create_i = 0; create_i < STARCOUNT; create_i++) {
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
		geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
		geometry.push_back(((float)((rand() % 10000)/10000.0f))*10.0f);
		//std::cout << "Initial fill " << create_i << std::endl;
	}

    GLfloat* res = new GLfloat[2];
    res[0] = c.w;
    res[1] = c.h;
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    delete res;

    GLfloat pProjMat[16] = {0};
    getPProjMat(pProjMat, 60.0, ((float)c.w)/((float)c.h));
    glUniformMatrix4fv(shaderProgram.getUfmHandle("projection"), 1, GL_FALSE, pProjMat);

    GLfloat xr[16] = {0};
    GLfloat yr[16] = {0};
    GLfloat zr[16] = {0};

    struct timeval tTmp;
    struct timeval startT;
    struct timezone tz;
    float t = 0.0f;
    float fpsLastT = 0.0f;
    unsigned int frames = 0;

    gettimeofday(&tTmp, &tz);
    gettimeofday(&startT, &tz);

    for (;;)
    {
        check();

        gettimeofday(&tTmp, &tz);
        t = static_cast<float>(tTmp.tv_sec - startT.tv_sec + ((tTmp.tv_usec - startT.tv_usec) * 1e-6));
        glUniform1f(shaderProgram.getUfmHandle("iGlobalTime"), t);
/*
		for (int test_i=STARCOUNT*3; test_i>0; test_i-=3) {
			if (geometry[test_i] < 0.0f)
				geometry.erase(geometry.begin() + (test_i-2), geometry.begin() + (test_i));
			//std::cout << "Test and delete " << test_i << std::endl;
		}

		for (int mov_i=0; mov_i<STARCOUNT*3-2; mov_i+=3) {
			geometry[mov_i]-=0.0001;
			//std::cout << "Move " << mov_i << std::endl;
		}

		while (geometry.size() < STARCOUNT*3) {
			geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
			geometry.push_back((((float)((rand() % 10000)/10000.0f))-0.5f)*10.0f);
			geometry.push_back(10.0f);
			//std::cout << "Fill new" << std::endl;
		}
*/
        getXRotMat(xr, t*0.2);
        getYRotMat(yr, t*0.8);
        getZRotMat(zr, t*0.6);

        glUniformMatrix4fv(shaderProgram.getUfmHandle("xRotation"), 1, GL_FALSE, xr);
        glUniformMatrix4fv(shaderProgram.getUfmHandle("yRotation"), 1, GL_FALSE, yr);
        glUniformMatrix4fv(shaderProgram.getUfmHandle("zRotation"), 1, GL_FALSE, zr);

        glVertexAttribPointer(shaderProgram.getAtrHandle("vertex"), 3, GL_FLOAT, GL_FALSE, 0, &geometry[0]);
        glEnableVertexAttribArray(shaderProgram.getAtrHandle("vertex"));

        glDrawArrays(GL_POINTS, 0, geometry.size()/3);

        window.swapBuffers();

        if (c.fpsCounter)
        {
            frames++;
            if (frames > c.fpsIn)
            {
                cout << "FPS=" << (c.fpsIn / (t - fpsLastT)) << endl;
                fpsLastT = t;
                frames = 0;
            }
        }
    }
    return 0;
}
