#include "AudioComponent.h"
#include <iostream>

AudioComponent::AudioComponent()
{
    //ctor
    engine_ = irrklang::createIrrKlangDevice();
}

AudioComponent::~AudioComponent()
{
    //dtor
    engine_->drop();
}

void AudioComponent::play() {
    std::cout << "Time to Belieb!" << std::endl;
    if(audio_sources[now_playing_]) {
        engine_->play2D(now_playing_.c_str(), true);
    }
}

void AudioComponent::playOnce() {

}

void AudioComponent::pause() {
    //engine_->getSoundSource();
}

void AudioComponent::restart() {

}

bool AudioComponent::addAudioSource(std::string path_to_file, bool setActive = false) {

    irrklang::ISound* audio = engine_->play2D(path_to_file.c_str());
    if(audio) {
        audio_sources.insert({path_to_file, audio});

        if(setActive)
            now_playing_ = path_to_file;
    }

}
