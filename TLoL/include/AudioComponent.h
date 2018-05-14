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
        void play();                            ///
        bool play(std::string);
        void playOnce();
        bool playOnce(std::string);
        void restart();
        void pause();
        bool registerAudioSource(std::string);
        //bool setActiveAudio(std::string);
        irrklang::ISoundEngine* engine_;

    protected:

    private:
        std::string last_played_;

        std::unordered_map<std::string, irrklang::ISound*> audio_sources;
};

#endif // AUDIOCOMPONENT_H
