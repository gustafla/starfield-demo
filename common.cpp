#include "common.hpp"

CommonData::CommonData(unsigned int x, unsigned int y):
t(0.0f),
beatHalfSine(0.0f) {
    halfYRes[0] = res[0] = x;
    res[1] = y;
    halfYRes[1] = y/2;
}
