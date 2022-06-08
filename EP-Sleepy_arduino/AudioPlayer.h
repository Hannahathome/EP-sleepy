#ifndef AUDIOPLAYER_H // if not defined, do the following: (aka the rest of the code until endif) 
#define AUDIOPLAYER_H // These are also called define guards  

#include <MD_YX5300.h>
#include <SoftwareSerial.h>

#define ESP_RX = 16; // this is the RX2 pin
#define ESP_TX = 17; // this is the TX2 pin
SoftwareSerial serialStream(ESP_RX, ESP_TX); // The serial stream used by the mp3 player
MD_YX5300 player = MD_YX5300(serialStream);  // MP3 player

enum Folders {
  questionaire = 0x00, //for now i just use the one folder, so all parts are in questionaire 
  //stories = 0x01
};

enum QuestionaireFiles {
  INTRO = 0X01,
  Q1 = 0X02,
  Q2 = 0X03,
  Q3 = 0X04,
  Q4 = 0X05,
  Q5 = 0X06,
  Q6 = 0X07,
  Q7 = 0X08,
  Q8 = 0X09,
  Q9 = 0X0A,
  Q10 = 0X0B,
  Q11 = 0X0C,
  Q12 = 0X0D,
  OUTRO = 0X0E,
  OUTRO_STORY = 0X0F,
};

enum StoryFiles {
  STORY_1 = 0X10,
  STORY_2 = 0X11,
  STORY_3 = 0X12,
  STORY_4 = 0X13,
  STORY_5 = 0X14
};

class AudioPlayer {
  private:



  public:
    AudioPlayer() {
      Serial.println("Audio setup - Start");
      serialStream.begin(9600);
      player.begin();
      Serial.println("Audio setup - Finished");
    }
    
    void PlayIntro() { 
      player.playTrack(QuestionaireFiles::INTRO);
    } 

    void PlayOutro() {
      player.playTrack(QuestionaireFiles::OUTRO_STORY); //versturen commando naar mp3 --> speel muziek
    }

    void PlayQuestion(uint8_t question) {
      player.playTrack(question);
    }

    void PlayStory(uint8_t storyPart) {
      player.playTrack(storyPart);
    }
};

#endif