#pragma once
#include <SFML/Audio.hpp>

class Audio{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string source;
public:
	Audio(std::string src);
	Audio();
	~Audio();

	void load(std::string src);
	void play();
	void stop();
	void setVolume(float vol);


};

