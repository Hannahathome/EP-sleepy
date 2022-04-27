// LIBRARIES
//#include <OOCSI.h>              // send data to oocsi (not yet implemented)
//#include <EEPROM.h>             // saving data in the memory of ESP (not yet implemented)
#include <MD_YX5300.h>            // MD_YX5300 MP3 Player 
#include <SoftwareSerial.h>

//AUDIO PLAYER--------------------------------------------------//
//Defining the pins
#define ESP_RX 16 // this is the RX2 pin 
#define ESP_TX 17 // this is the TX2 pin 
SoftwareSerial mySerial(ESP_RX, ESP_TX);

//COMAND SENDING
static int8_t Send_buf[8] = {0} ;   // a space for the command to be send ( the command is a set of numbers)

//PLAYING OR PAUSING
unsigned char playmode = 1;
#define PLAY_SOUND  1
#define PAUSE_SOUND 0

//CONTROL BUTTON
//int BUTTON_START = 34;              //Control button pin

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

/*--------------------Specifications-----------------------*/
#define FOLDER_ONE 0X00
#define INTRO 0X01
#define Q1 0X02
#define Q2 0X03
#define Q3 0X04
#define Q4 0X05
#define Q5 0X06
#define Q6 0X07
#define Q7 0X08
#define Q8 0X09
#define Q9 0X10
#define Q10 0X11
#define Q11 0X12
#define Q12 0X13
#define OUTRO 0X14
#define OUTRO_STORY 0X15

char TheQuestions[] = {Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12};

#define FOLDER_TWO 0X01
#define STORY_1 0X01
#define STORY_2 0X02
#define STORY_3 0X03
#define STORY_4 0X04
#define STORY_5 0X05
/*********************************************************************/

//QUESTIONS--------------------------------------------------//
int QUESTION_AMOUNT = 12;

//BUTTONS--------------------------------------------------//

//define the buttons pins
int BUTTON_START = 34;  // GI(O)P 34 pin connected to button (CAREFUL! INPUT ONLY pin, this pin does not give any OUTPUT, so do not use if for that)
int BUTTON_ONE = 27;    // GIOP 27 pin connected to button
int BUTTON_TWO = 26;    // GIOP 26 pin connected to button
int BUTTON_THREE = 25;  // GIOP 25 pin connected to button
int BUTTON_FOUR = 33;   // GIOP 33 pin connected to button
int BUTTON_FIVE = 32;   // GIOP 32 pin connected to button


//LIGHTS IN BUTTONS--------------------------------------------------//
#define NUM_LEDS     6

int delayTime = 500;  // duration to pause

int latchPin = 15;    // the pin connected to the latch pin, RCLK (pin 12 of the shift register)setting the latch LOW will send the 8 bits in storage to the output pins
int clockPin = 21;    // the pin connected to the clock pin, SRCLK (pin 11 of the shift register)
int dataPin = 4;      // the pin connected to the serial data pin, SER (pin 14 of the shift register)
byte storageByte;


void setup () {
  //AUDIO PLAYER--------------------------------------------------//
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("START");
  delay(500);

  //PLAY/PAUSE SETUP
  attachInterrupt(BUTTON_START, playOrPause, RISING); //pin2 -> INT0, and the Touch Sensor is connected with pin2 of Arduino

  //CONNECT TO THE YX5300 Serial MP3 Player
  sendCommand(SELECT_DEVICE, 0, DEVICE_TF);           // select device command, empty space, device command
  delay(200);
  playOrPause();                                      //void for the playing and pausing (starts on paused)

  Serial.println("Audio setup");

  //BUTTONS--------------------------------------------------//
  // initialize the pushbutton pin as an input
  pinMode(BUTTON_ONE, INPUT);
  pinMode(BUTTON_TWO, INPUT);
  pinMode(BUTTON_THREE, INPUT);
  pinMode(BUTTON_FOUR, INPUT);
  pinMode(BUTTON_FIVE, INPUT);
  pinMode(BUTTON_START, INPUT);

  Serial.println("Buttons setup");

  //LIGHTS IN BUTTONS--------------------------------------------------//
  // initialize all the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.println("Lights setup");

  /***************************************************/
  //THE ACTUAL LIKE PROGRAM THAT RUNS ONCE--------------------------------------------------//
  Serial.println("Starting system");
  //first lights
  blinkLights ();
  blinkLights ();

  //introduction text
  sendCommand(PLAY_W_INDEX, FOLDER_ONE, INTRO);
  delay (17000); //waiting for the text to finish
  //checkButton();
  buttonWait(BUTTON_START); //waiting for the button to be pressed
  playQuestionOne ();

  walkingLights (); //anything after playig the sound will happen during the playing, beware of this
  Serial.println("end of the program"); 

}

/***************************************************/

void loop() {

}


//  auto buttons = Buttons();
//  auto player = AudioPlayer();
//
//  buttons.PlayStartAnimation();
//  player.PlayIntro();
//
//  buttons.ShowNextButtonAndWait();
//
//  std::string answers[QUESTION_AMOUNT] = {};
//  for (int i = 0; i < QUESTION_AMOUNT; i++) {
//    player.PlayQuestion(questions[i].audioFileLocation);
//    answers[i] = buttons.GetUserAnswer();
//  }
//
//  auto saver = Saver();
//  saver.Save(answers, QUESTION_AMOUNT);
//
//  player.PlayOutro();
//  player.PlayStory();
//  player.PlayEndText();

//return 0;
