#include "Audio.h"



Audio::Audio(std::string src){
	source = src;
	buffer.loadFromFile(src);
	sound.setBuffer(buffer);
	sound.setVolume(100.f); //set default volume
}

Audio::Audio() {
}


Audio::~Audio(){
}

void Audio::load(std::string src) {
	source = src;
	buffer.loadFromFile(src);
	sound.setBuffer(buffer);
	sound.setVolume(100.f); //set default volume
}

void Audio::play(){
	sound.play();
}

void Audio::stop() {
	sound.stop();
}

void Audio::setVolume(float vol) {
	sound.setVolume(vol);
}




