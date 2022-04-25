#include <string>
#include <iostream>



class AudioPlayer {
public:
  AudioPlayer();

  void PlayIntro();
  void PlayQuestion(std::string questionFileLocation);
  void PlayOutro();
  void PlayStory();
  void PlayEndText();
};

AudioPlayer::AudioPlayer() {
  std::cout << "Hello and welcome!\n";
  
}

void AudioPlayer::PlayIntro() {
  std::cout << "This is the intro that is being played\n";
  
}



void AudioPlayer::PlayQuestion(std::string questionFileLocation) {
  std::cout << questionFileLocation << "\n";
}

void AudioPlayer::PlayOutro() {
  std::cout << "Thank you for your answers.\n";
}

void AudioPlayer::PlayStory() {
  std::cout << "Imagine a great story here, that would be great.\n";
}

void AudioPlayer::PlayEndText() {
  std::cout << "The program will now stop\n";
  system("pause");
}
