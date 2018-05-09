#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H
#include "MediaControlsInterface.h"
#include <irrklang.h>

class AudioComponent : public MediaControlsInterface
{
    public:
        AudioComponent();
        ~AudioComponent();
        void play();
        void playOnce();
        void restart();
        void pause();

    protected:

    private:
        irrklang::ISoundEngine* engine_;
};

#endif // AUDIOCOMPONENT_H
