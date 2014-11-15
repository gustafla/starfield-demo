#ifndef COMMON_HPP
#define COMMON_HPP

class CommonData {
    public:
        CommonData(unsigned int x, unsigned int y);

        float t;
        float res[2];
        float halfYRes[2];
        float beatHalfSine;
};

#endif
