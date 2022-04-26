/*
   Using this code you can test the MP3 Player part (YX5300 Serial MP3 Player/Catalex player)

   Save the songs you want to play in a folder called 01 and 02 on the SD card. The sounds should be called 001-XXX, 002-XXX etc.

   This code was written by Hannah van Iterson
   Code heavily inspired  by:
   https://github.com/rdiot/rdiot-b208/blob/master/SerialMp3PlayerControl.ino.ino
   https://github.com/rdiot/rdiot-b208/blob/master/Serial%20MP3%20Player%20v1.0%20Manual.pdf = MANUAL! PLS READ THIS

*/

#include <SoftwareSerial.h>
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
int BUTTON_START = 34;              //Control button pin 

//VOLUME
#define ROTARY_ANGLE_SENSOR 35      //Pin of the POD meter 
#define ADC_REF 5                   //reference voltage of ADC is 5v
#define VCC     5                   //the default value of VCC of the control interface is 5v
#define FULL_ANGLE 280              //full value of the rotary angle is 280 degrees


/************Command byte**************************/
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
/*********************************************************************/
#define FOLDER_ONE 0X00

#define PLAY_INTRO 0X01
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
#define PLAY_OUTRO 0X14
#define PLAY_OUTRO_STORY 0X15


#define FOLDER_TWO 0X01
#define STORY_1 0X01
#define STORY_2 0X02
#define STORY_3 0X03
#define STORY_4 0X04
#define STORY_5 0X05


void setup()
{
  //pinMode(2, INPUT); // Button - Paluse&Play
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("START");
  delay(500);

  //PLAY/PAUSE SETUP
  attachInterrupt(BUTTON_START, playOrPause, RISING); //pin2 -> INT0, and the Touch Sensor is connected with pin2 of Arduino

  //CONNECT TO THE YX5300 Serial MP3 Player
  sendCommand(SELECT_DEVICE, 0, DEVICE_TF);           // select device command, empty space, device command
  delay(200);
  // sendCommand(PLAY_W_VOL, 0X0F01);                 // volume thing
  playOrPause();                                      //void for the playing and pausing (starts on paused)
  sendCommand(PLAY_W_INDEX, FOLDER_ONE, PLAY_INTRO);
}
static int8_t pre_vol = 0x0f;


void loop() {
  //VOLUME
  //  int degrees;
  //  degrees = getDegree();
  //  int8_t volume;
  //
  //  volume = map(140, 0, 280, 30, 0);   //The degrees is 0~280, should be converted to be 0~255 to control the brightness of LED
  //  if (volume != pre_vol)
  //  {
  //    sendCommand(SET_VOLUME, volume);
  //    pre_vol = volume;
  //  }
  delay(100);
}

void sendCommand(int8_t command, byte option1, byte option2) {
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

//FOR VOLUME (To be added)
//  int getDegree(){
//  int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
//  Serial.println(sensor_value);
//  float voltage;
//  voltage = (float)sensor_value*ADC_REF/4095;
//  float degrees = (voltage*FULL_ANGLE)/VCC;
//  return degrees;
//}

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
    sendCommand(PLAY, 0 ,0 );
    Serial.println("play");
  }
  sei();//turn on interrupt
}
