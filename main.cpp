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

#include <pthread.h>
#include <cstdlib>
#include "demo_thread.hpp"
#include "getch.hpp"

/*     (some :D) ERROR CODES:
 *
 *  1 - Shader program failed to compile/link
 *  2 - Failed to create window
 */

void cleanup() {
    getchRecov();
}

int main(int argc, char *argv[])
{
    atexit(cleanup);
    DemoArg demoArg;
    demoArg.argc = argc;
    demoArg.argv = argv;
    pthread_t demoThread;
    pthread_create(&demoThread, NULL, playDemo, (void*)&demoArg);
    
    /*
     * Yes. Demo in a separate thread and main() waiting for ESC using a weird
     * c lib dependent piece of code.
     * Why does it have to be this hard?
     */

    char const ESC = 27;
    char c=0;
    for (;;) {
        c = getch();
        if (c == ESC)
            break;
    }
    return 0;
}
