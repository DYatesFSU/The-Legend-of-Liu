#include "AudioComponent.h"

AudioComponent::AudioComponent() {
    //sound_engine_= irrklang::createIrrKlangDevice();
}


AudioComponent::AudioComponent(std::string path_to_song) {
    //sound_engine_= irrklang::createIrrKlangDevice();
    path_to_song_ = path_to_song;
}



AudioComponent::~AudioComponent() {
    sound_engine_->drop();
}

void AudioComponent::setSourceFile(std::string path_to_song) {
    path_to_song_ = path_to_song;
}
void AudioComponent::play() {
    //sound_engine_->play2D(song_, true);
}

void AudioComponent::playOnce() {
    //sound_engine_->play2D(song_, false);
}

void AudioComponent::pause() {
    //song_->setIsPaused(true);
}
void AudioComponent::restart() {
    sound_engine_->drop();
    init();
}

void AudioComponent::init() {
   // song_ = sound_engine_::addSoundSourceFromFile(path_to_song_);
}
