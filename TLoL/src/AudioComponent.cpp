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
    if(audio_sources[last_played_]) {
        engine_->play2D(last_played_.c_str(), true);
    }
}

bool AudioComponent::play(std::string path_to_file) {
std::cout << "Attempting to play " << path_to_file << std::endl;
    bool success = false;
    irrklang::ISound * sound = audio_sources[path_to_file];
    if(sound) {

        if (sound->getIsPaused()) {
            sound->setIsPaused(false);
            std::cout << "Sound was paused " << path_to_file << " " << std::endl;
        } else {
            sound->stop();
            registerAudioSource(path_to_file);
            play(path_to_file);
            std::cout << "Registering: " << path_to_file << " " << std::endl;
        }

        success = true;
    } else {
        std::cout << "file " << path_to_file << " is not registered" << std::endl;
    }

    return success;
}

void AudioComponent::playOnce() {

}

bool AudioComponent::playOnce(std::string path_to_file) {
    //std::cout << "Attempting to play " << path_to_file << " one time" << std::endl;
    bool success = false;
    irrklang::ISound * sound = audio_sources[path_to_file];
    if(sound) {

        if (sound->getIsPaused()) {
            sound->setIsPaused(false);
            std::cout << "Sound was paused " << path_to_file << " " << std::endl;
        } else {
            sound->stop();
            registerAudioSource(path_to_file);
            playOnce(path_to_file);
            std::cout << "Registering: " << path_to_file << " " << std::endl;
        }

        success = true;
    } else {
        std::cout << "file " << path_to_file << " is not registered" << std::endl;
    }

    return success;
}

void AudioComponent::pause() {

    if(last_played_.empty())
        if(!audio_sources[last_played_]->isFinished())
            audio_sources[last_played_]->setIsPaused(true);


    //engine_->getSoundSource();
}

void AudioComponent::restart() {

}

bool AudioComponent::registerAudioSource(std::string path_to_file) {

    bool result = false;

    irrklang::ISound* audio = engine_->play2D(path_to_file.c_str(), false, true);

    if(audio) {
        audio_sources[path_to_file] = audio;

        result = true;
    }

    return result;
}
