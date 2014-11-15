#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "alsa/asoundlib.h"
#include <string>

/*
 * Only stereo, S16_LE, for now
 */

class AudioOut {
    public:
        AudioOut(std::string idevice="default", unsigned int ibufferSize=512, unsigned int isampleRate=44100);
        ~AudioOut();
        int16_t* getS16Buffer();
        int writeBufOut();
        unsigned int getBufferSize();
        bool wantData();
        void stop();
    private:
        unsigned int bufferSize;
        int16_t* S16Buffer;
        int err;
        snd_pcm_t* alsaPlaybackHandle;
        snd_pcm_hw_params_t* alsaHWparams;
        unsigned int sampleRate;
};

#endif
