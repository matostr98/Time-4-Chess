#pragma once
#include <map>
#include "Audio.h"

class AudioManager{
private:
	std::map<std::string, Audio> audio;
public:
	void loadAudio(std::string src, std::string name);
	void play(std::string name);
	void stop(std::string name);
	void setVolume(std::string name, float vol);
};

