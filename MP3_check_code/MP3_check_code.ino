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

//PLAYING OR PAUSING
unsigned char playmode = 1;
#define PLAY_SOUND  1
#define PAUSE_SOUND 0
static int8_t Send_buf[8] = {0} ;   //Send the command

int BUTTON_START = 34;              //Control button

//VOLUME
#define ROTARY_ANGLE_SENSOR 35      //Pin of the POD meter 

#define ADC_REF 5                   //reference voltage of ADC is 5v
#define VCC     5                   //the default value of VCC of the control interface is 5v
#define FULL_ANGLE 280              //full value of the rotary angle is 280 degrees


/************Command byte**************************/
#define NEXT_SONG 0X01
#define PREV_SONG 0X02
#define PLAY_W_INDEX 0X03
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


void setup()
{
  //pinMode(2, INPUT); // Button - Paluse&Play
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("START");
  delay(500);

  //PLAY/PAUSE SETUP
  attachInterrupt(BUTTON_START, playOrPause, RISING); //pin2 -> INT0, and the Touch Sensor
  //is connected with pin2 of Arduino

  //CONNECT TO THE YX5300 Serial MP3 Player
  sendCommand(SELECT_DEVICE, DEVICE_TF);
  delay(200);
  sendCommand(PLAY_W_VOL, 0X0F01);
  playOrPause();                                      //void for the playing and pausing (starts on paused)
}
static int8_t pre_vol = 0x0f;


void loop() {
  //VOLUME
  //  int degrees;
  //  degrees = getDegree();
  int8_t volume;

  volume = map(140, 0, 280, 30, 0);   //The degrees is 0~280, should be converted to be 0~255 to control the brightness of LED
  if (volume != pre_vol)
  {
    sendCommand(SET_VOLUME, volume);
    pre_vol = volume;
  }
  delay(100);
}

void sendCommand(int8_t command, int16_t dat) {
  delay(20);
  Serial.println("Command");          // As explained in the manual linked above each signal has their own 'code' they can be found in the manual. They do not need to be edited.
  Send_buf[0] = 0x7e;                 // Every command starts with this, lets call it the 'address'
  Send_buf[1] = 0xff;                 // Version info
  Send_buf[2] = 0x06;                 // Number of bytes
  Send_buf[3] = command;              // The command, as defined earlier (PLAY, PAUSE etc)
  Send_buf[4] = 0x00;//               // always 00, lets call it a spacer
  Send_buf[5] = (int8_t)(dat >> 8);   // datah
  Send_buf[6] = (int8_t)(dat);        // datal
  Send_buf[7] = 0xef; //              // Ending the command

  for (uint8_t i = 0; i < 8; i++)     //
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
    sendCommand(PAUSE, 0);
    Serial.println("pause");
  }
  else
  {
    playmode = PLAY_SOUND;
    sendCommand(PLAY, 0);
    Serial.println("play");
  }
  sei();//turn on interrupt
}
