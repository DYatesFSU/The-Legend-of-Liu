#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H
#include <audioControlsInterface.h>
#include <unordered_map>
#include <irrklang.h>

class AudioComponent : public AudioControlsInterface
{
    public:
        AudioComponent();
        ~AudioComponent();
        void play();
        void playOnce();
        void restart();
        void pause();
        bool addAudioSource(std::string, bool);

    protected:

    private:
        std::string now_playing_;
        irrklang::ISoundEngine* engine_;
        std::unordered_map<std::string, irrklang::ISound*> audio_sources;
};

#endif // AUDIOCOMPONENT_H
