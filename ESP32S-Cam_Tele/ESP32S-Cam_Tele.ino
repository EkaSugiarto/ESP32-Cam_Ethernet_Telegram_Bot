//Library bawaan example ESP32-Cam
#include "esp_camera.h"
#include "Arduino.h"
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"

//Config pin-pin
#include "Confignya.h"

//Config SPIFFS
#include "SPIFFSnya.h"

//Config LAN
#include "LANConfig.h"

void setup() {
  //Memulai definisi pin-pin
  Confignya();

  //Setup SPIFFS
  SPIFFSS();

  //Setup NTP
  NTPS();

  Serial.begin(9600);
}

void loop() {
  //Fungsi loop untuk ethernet
  LANCheck();
  SensorL();
}