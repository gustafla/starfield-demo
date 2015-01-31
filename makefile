# Copyright 2014 Lauri Gustafsson
#
# This file is part of [DEMO NAME].
#
#     [DEMO NAME] is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     [DEMO NAME] is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
#

# A makefile to build [DEMO NAME].

SRCS = rpi_gfx.cpp main.cpp util.cpp config.cpp text.cpp gfx_EGL_window.cpp gfx_shader.cpp gfx_texture_2D.cpp tga_file.cpp gfx_mat.cpp obj_iobject.cpp gfx_screen.cpp effects/point_field/point_field.cpp common.cpp gfx_postprocessor.cpp effects/point_flag/point_flag.cpp parts/starfield.cpp parts/flag.cpp gfx_noise_texture.cpp audio.cpp wav_player.cpp getch.cpp types.cpp demo_thread.cpp audio_thread.cpp cleanup.cpp parts/plasma_bars.cpp parts/intro.cpp fade.cpp demo_timing.cpp gfx_model.cpp parts/cube.cpp gfx_model_handler.cpp alt_main.cpp gfx_screen_movable.cpp
TARGET = starfield
OBJS = $(SRCS:.cpp=.o)
CFLAGS += -O2 -fomit-frame-pointer -MMD -MP
debug: CFLAGS = -g
INCLUDES += -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I./ -I/opt/vc/src/hello_pi/libs/ilclient -I/opt/vc/src/hello_pi/libs/vgfont
LFLAGS = -L/opt/vc/lib/ -L/opt/vc/src/hello_pi/lib/ilclient -L/opt/vc/src/hello_pi/lib/vgfont
LIBS = -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lm -lrt -lasound
CC = g++

all: $(TARGET)
	@echo "Finished."
	strip --strip-all $(TARGET)

debug: $(TARGET)
	@echo "Finished"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS) $(LIBS_CUSTOM)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET)
	find . -name "*.o" -type f -delete
	find . -name "*.d" -type f -delete
	
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

-include *.d
