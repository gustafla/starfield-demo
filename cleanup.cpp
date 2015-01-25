#include "getch.hpp"
#include "rpi_gfx.hpp"
#include "cleanup.hpp"

void cleanup() {
    getchRecov();
    bcm_host_deinit();
}
