#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H
#include "MediaControlsInterface.h"

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
};

#endif // AUDIOCOMPONENT_H
