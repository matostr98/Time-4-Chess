#include "MusicManager.h"


//TODO random without the same song twice
int MusicManager::randomSong() {
	static std::default_random_engine e{};
	std::uniform_int_distribution<int> d(0, songs-1);
	return d(e);
}

MusicManager::MusicManager() {
	songs = 0;
	//ind = 0;
}

MusicManager::~MusicManager()= default;

void MusicManager::setVolume(float vol) {
	music.setVolume(vol);
}

void MusicManager::play() {
	music.openFromFile(sources[randomSong()]);
	music.play();
}

void MusicManager::add(std::string src){
	sources.push_back(src);
	songs++;
}

void MusicManager::next(){
	if (music.getStatus() == sf::Music::Status::Stopped) {
		music.openFromFile(sources[randomSong()]);
		music.play();
	}
}



