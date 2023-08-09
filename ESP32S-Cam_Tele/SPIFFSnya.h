#include "esp32-hal-gpio.h"
#include "FS.h"
#include <SPIFFS.h>

File file;

void SPIFFSS();
void LampuIROn();
void LampuIROff();

void TakePhoto() {
  LampuIROn();
  file = SPIFFS.open("/foto.jpg", FILE_WRITE);

  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }

  camera_fb_t *fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  file.write(fb->buf, fb->len);

  delay(1000);

  esp_camera_fb_return(fb);

  file.close();
  LampuIROff();
}

void SPIFFSS() {
  if (!SPIFFS.begin(false)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS aman");
}

//Fungsi untuk menyalakan lampu IR dengan memberikan sinyal PWM ke modul Trigger Mosfet PWM
void LampuIROn() {
  digitalWrite(IRpin, HIGH);
}

void LampuIROff() {
  digitalWrite(IRpin, LOW);
}