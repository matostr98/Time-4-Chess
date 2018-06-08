#pragma once
#include <vector>
#include <map>
#include <random>
#include <SFML/Audio/Music.hpp>

class MusicManager
{
private:
	std::vector<std::string> sources;	
	sf::Music music;
	int randomIndex();
	int randomSong();
	int songs;
	std::vector<int> index;
	int ind;
public:
	MusicManager();
	~MusicManager();

	void setVolume(float vol);
	void play();
	void add(std::string src);
	void next();
	//void previous();
};

