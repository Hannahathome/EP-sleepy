/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/


#//include <esp_now.h>
#include <WiFi.h>
#include <OOCSI.h>

//OOCSI CONNECTION --> you need the name an password of your wifi network for this
//const char* ssid = "your network name"; // SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
//const char* password = "your network password"; // Password of your Wifi network.
//
//const char* OOCSIName = "your oocsi handle"; // name for connecting with OOCSI (unique handle)
//const char* hostserver = "your oocsi address .nl"; // put the adress of your OOCSI server here, can be URL or IP address string

//const char* ssid = "Langeboomgaard"; // SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
//const char* password = "ACvI4152EK"; // Password of your Wifi network.
////
const char* ssid = "Van Dijk"; // SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
const char* password = "NFuu6bbe4fuv"; // Password of your Wifi network.
//
//const char* ssid = "jandel0309"; // SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
//const char* password = "jandel0309"; // Password of your Wifi network.

const char* OOCSIName = "EP_SLEEPY_Hannah"; // name for connecting with OOCSI (unique handle)
const char* hostserver = "oocsi.id.tue.nl"; // put the adress of your OOCSI server here, can be URL or IP address string




// OOCSI reference for the entire sketch. To connect to an OOCSI network, that is, a running OOCSI server, you first need to create an OOCSI reference:
OOCSI oocsi = OOCSI();

void OOCSIInitialization() {
  WiFi.mode(WIFI_STA);   // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  oocsi.connect(OOCSIName, hostserver, ssid, password);   // Connect to OOCSI
}

void SendAnswers() {
  //sending data to OOCSI (for now
  oocsi.newMessage("EP_very_sleepy"); //channel name
  //oocsi.addString("ESP MyBeaker", "dde85752348b14fb9");
  oocsi.addIntArray("answers", answers, QUESTION_AMOUNT );
  oocsi.sendMessage();
  oocsi.check();
  //Serial.println (String(oocsi.check())); 
}
