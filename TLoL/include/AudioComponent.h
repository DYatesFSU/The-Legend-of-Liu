#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H
#include <irrKlang.h>
#include <ik_ISound.h>
#include <string>
#include <MediaControlsInterface.h>

class AudioComponent : public MediaControlsInterface
{
    public:
        AudioComponent();
        AudioComponent(std::string);
        ~AudioComponent();

        void play();                                ///< Plays the audio file continously in a loop
        void playOnce();                            ///< Plays the audio file once
        void pause();                               ///< Temporarily stops audio playback
        void restart();                             ///< Restarts the audio file from the beginning
        void setSourceFile(std::string);
    protected:

    private:
        irrklang::ISoundEngine* sound_engine_;
        irrklang::ISoundSource* song_;
        std::string path_to_song_;
        void init();            ///< Initializes the AudioComponent.

};

#endif // AUDIOCOMPONENT_H
