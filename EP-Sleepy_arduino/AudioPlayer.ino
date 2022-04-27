/*
  Functions you can call from this file:

  void sendCommand(int8_t command, byte option1, byte option2)

  Fill in the Command byte, and add options from the lower list.
  If you do not need the additional options, add a '0'
*/

///*--------------------Command byte-----------------------*/
//#define NEXT_SONG 0X01
//#define PREV_SONG 0X02
//#define PLAY_W_INDEX 0X03   //only play this song
//#define VOLUME_UP 0X04
//#define VOLUME_DOWN 0X05
//#define SET_VOLUME 0X06
//#define SINGLE_CYCLE_PLAY 0X08
//#define SELECT_DEVICE 0X09
//#define DEVICE_TF 0X02
//#define SLEEP_MODE 0X0A
//#define WAKE_UP 0X0B
//#define RESET 0X0C
//#define PLAY 0X0D
//#define PAUSE 0X0E
//#define PLAY_FOLDER_FILE 0X0F
//#define STOP_PLAY 0X16
//#define FOLDER_CYCLE 0X17
//#define SET_SINGLE_CYCLE 0X19
//#define SINGLE_CYCLE_ON 0X00
//#define SINGLE_CYCLE_OFF 0X01
//#define SET_DAC 0X1A
//#define DAC_ON  0X00
//#define DAC_OFF 0X01
//#define PLAY_W_VOL 0X22
//
///*--------------------Specifications-----------------------*/
//#define FOLDER_ONE 0X00
//#define INTRO 0X01
//#define Q1 0X02
//#define Q2 0X03
//#define Q3 0X04
//#define Q4 0X05
//#define Q5 0X06
//#define Q6 0X07
//#define Q7 0X08
//#define Q8 0X09
//#define Q9 0X10
//#define Q10 0X11
//#define Q11 0X12
//#define Q12 0X13
//#define OUTRO 0X14
//#define OUTRO_STORY 0X15
//
//#define FOLDER_TWO 0X01
//#define STORY_1 0X01
//#define STORY_2 0X02
//#define STORY_3 0X03
//#define STORY_4 0X04
//#define STORY_5 0X05
///*********************************************************************/



void sendCommand(uint8_t command, uint8_t option1, uint8_t option2) {
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


void playOrPause() {
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



//class AudioPlayer {
//  public:
//    AudioPlayer();
//
//    void PlayIntro();
//    void PlayQuestion(std::string questionFileLocation);
//    void PlayOutro();
//    void PlayStory();
//    void PlayEndText();
//};
//
//AudioPlayer::AudioPlayer() {
//  std::cout << "Hello and welcome!\n";
//
//}
//
//void AudioPlayer::PlayIntro() {
//  std::cout << "This is the intro that is being played\n";
//
//}
//
//void AudioPlayer::PlayQuestion(std::string questionFileLocation) {
//  std::cout << questionFileLocation << "\n";
//}
//
//void AudioPlayer::PlayOutro() {
//  std::cout << "Thank you for your answers.\n";
//}
//
//void AudioPlayer::PlayStory() {
//  std::cout << "Imagine a great story here, that would be great.\n";
//}
//
//void AudioPlayer::PlayEndText() {
//  std::cout << "The program will now stop\n";
//  system("pause");
//}
