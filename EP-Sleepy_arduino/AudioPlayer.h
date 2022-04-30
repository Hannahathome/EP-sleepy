/*
  Functions you can call from this file:

  void sendCommand(int8_t command, byte option1, byte option2)

  Fill in the Command byte, and add options from the lower list.
  If you do not need the additional options, add a '0'
*/

#ifndef AUDIOPLAYER_H               // if not defined, do the following: (aka the rest of the code until endif) 
#define AUDIOPLAYER_H

#include <MD_YX5300.h>              // MD_YX5300 MP3 Player 
#include <SoftwareSerial.h>

//AUDIO PLAYER--------------------------------------------------//
//Defining the pins
#define ESP_RX 16                   // this is the RX2 pin 
#define ESP_TX 17                   // this is the TX2 pin 
SoftwareSerial mySerial(ESP_RX, ESP_TX);

//COMAND SENDING
static int8_t Send_buf[8] = {0} ;   // a space for the command to be send ( the command is a set of numbers)

//PLAYING OR PAUSING
unsigned char playmode = 1;
#define PLAY_SOUND  1
#define PAUSE_SOUND 0

/*--------------------Command byte-----------------------*/
#define NEXT_SONG 0X01
#define PREV_SONG 0X02
#define PLAY_W_INDEX 0X03   //only play this song
#define VOLUME_UP 0X04
#define VOLUME_DOWN 0X05
#define SET_VOLUME 0X06
#define SINGLE_CYCLE_PLAY 0X08
#define SELECT_DEVICE 0X09
#define DEVICE_TF 0X02
#define SLEEP_MODE 0X0A
#define WAKE_UP 0X0B
#define RESET 0X0C
#define PLAY 0X0D
#define PAUSE 0X0E
#define PLAY_FOLDER_FILE 0X0F
#define STOP_PLAY 0X16
#define FOLDER_CYCLE 0X17
#define SET_SINGLE_CYCLE 0X19
#define SINGLE_CYCLE_ON 0X00
#define SINGLE_CYCLE_OFF 0X01
#define SET_DAC 0X1A
#define DAC_ON  0X00
#define DAC_OFF 0X01
#define PLAY_W_VOL 0X22

enum Folders {
  questionaire = 0x00,
  stories = 0x01
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
  STORY_1 = 0X01,
  STORY_2 = 0X02,
  STORY_3 = 0X03,
  STORY_4 = 0X04,
  STORY_5 = 0X05
};

class AudioPlayer {
  private:
    static void playOrPause() {
      cli(); //turn off interrupt
      if (playmode == PLAY_SOUND)
      {
        playmode = PAUSE_SOUND;
        sendCommand(PAUSE, 0, 0);
        Serial.println("pause");
      }
      else
      {
        playmode = PLAY_SOUND;
        sendCommand(PLAY, 0 , 0 );
        Serial.println("play");
      }
      sei();//turn on interrupt
    }

    static void sendCommand(int8_t command, byte option1, byte option2) {
      delay(20);
      Serial.println("Command");          // As explained in the manual linked above each signal has their own 'code' they can be found in the manual. They do not need to be edited.
      Send_buf[0] = 0x7e;                 // Every command starts with this, lets call it the 'address'
      Send_buf[1] = 0xff;                 // Version info
      Send_buf[2] = 0x06;                 // Number of bytes
      Send_buf[3] = command;              // The command, as defined earlier (PLAY, PAUSE etc)
      Send_buf[4] = 0x00;//               // always 00, lets call it a spacer
      Send_buf[5] = option1 ;             // two bites as an option to e.g. select a specific folder
      Send_buf[6] = option2;              // two bites as an option to e.g. select a song
      Send_buf[7] = 0xef; //              // Ending the command

      for (uint8_t i = 0; i < 8; i++)     // this looks through all the send buffs, pastes them after one another and sends them.
      {
        mySerial.write(Send_buf[i]);
      }
    }

  public:
    void Initialize() {
      mySerial.begin(9600);
      attachInterrupt(Buttons::BUTTON_START, playOrPause, RISING); //pin2 -> INT0, and the Touch Sensor is connected with pin2 of Arduino

      //CONNECT TO THE YX5300 Serial MP3 Player
      sendCommand(SELECT_DEVICE, 0, DEVICE_TF);           // select device command, empty space, device command
      delay(200);
      playOrPause();                                      // void for the playing and pausing (starts on paused)

      Serial.println("Audio setup");
    }

    void PlayIntro() { 
      sendCommand(PLAY_W_INDEX, Folders::questionaire, QuestionaireFiles::INTRO); //versturen commando naar mp3 --> speel muziek (:: = a scope resolution operator. It means: "use" so, from QUESTIONAIREFILES use INTRO) 
    }

    void PlayOutro() {
      sendCommand(PLAY_W_INDEX, Folders::questionaire, QuestionaireFiles::OUTRO); //versturen commando naar mp3 --> speel muziek
    }

    void PlayQuestion(uint8_t question) {
      sendCommand(PLAY_W_INDEX, Folders::questionaire, question);

    }
};



#endif
