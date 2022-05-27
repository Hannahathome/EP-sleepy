#include <WiFi.h>
#include <OOCSI.h>

//OOCSI CONNECTION --> you need the name an password of your wifi network for this
const char* ssid = "your network name"; // SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
const char* password = "your network password"; // Password of your Wifi network.



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
