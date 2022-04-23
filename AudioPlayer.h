#include <string>

class AudioPlayer {
public:
  AudioPlayer();

  void PlayIntro();
  void PlayQuestion(std::string questionFileLocation);
  void PlayOutro();
  void PlayStory();
  void PlayEndText();
};

AudioPlayer::AudioPlayer() {}

void AudioPlayer::PlayIntro() {}

void AudioPlayer::PlayQuestion(std::string questionFileLocation) {}

void AudioPlayer::PlayOutro() {}

void AudioPlayer::PlayStory() {}

void AudioPlayer::PlayEndText() {}