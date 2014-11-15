#ifndef WAV_PLAYER_HPP
#define WAV_PLAYER_HPP

#include "audio.hpp"
#include <string>
#include <fstream>

/*
 * 16-bit for now
 */

class WavPlayer {
    public:
        WavPlayer(std::string filename, unsigned int ibufferSize=512);
        ~WavPlayer();
        int playFrame();
        bool done();
    private:
        AudioOut* playbackDevice;
        std::ifstream file;
        unsigned int size;
        unsigned int sampleRate;
        unsigned int bufferSize;
        void errorPrint(std::string filename);
        int err;
};

#endif
