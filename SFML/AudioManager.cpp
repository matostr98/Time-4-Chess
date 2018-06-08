#include "AudioManager.h"



void AudioManager::loadAudio(std::string src, std::string name) {
	audio[name].load(src);
}

void AudioManager::play(std::string name) {
	audio[name].play();
}
void AudioManager::stop(std::string name) {
	audio[name].stop();
}

void AudioManager::setVolume(std::string name, float vol) {
	audio[name].setVolume(vol);
}

