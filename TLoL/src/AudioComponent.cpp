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
    engine_->play2D("audio/bieber.ogg");
}

void AudioComponent::playOnce() {

}

void AudioComponent::pause() {

}

void AudioComponent::restart() {

}
