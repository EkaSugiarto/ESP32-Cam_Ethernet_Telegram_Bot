/*
Konfigurasi ethernet DHCP untuk bisa berkomunikasi dengan website yang HTTPS seperti telegram
Tutorial ada di website berikut
https://mischianti.org/2022/10/18/esp32-ethernet-w5500-with-plain-http-and-ssl-https/

Modul ethernet yang digunakan adalah W5500 dengan komunikasi
melalui jalur HSPI. Pin HSPI untuk ESP32 adalah sebagai berikut:
- MOSI di pin 13
- MISO di pin 12
- SCK  di pin 14
- SS   di pin 2
*/

#include <SPI.h>

//Library ini dibuat khusus untuk menggunakan modul Ethernet W5500 di ESP32-Cam
//Info selengkapnya ada di repositori berikut: https://github.com/arhi/EthernetSPI2/tree/master
#include <EthernetSPI2.h>

#include <SSLClient.h>
#include "trust_anchors.h"

byte mac[] = {
  0x02, 0xAB, 0xCD, 0xEF, 0x00, 0x01
};

EthernetClient base_client;
SSLClient client(base_client, TAs, (size_t)TAs_NUM, -1);

#include "NTPnya.h"
#include "Tele.h"

//Fungsi untuk setup dari ethernet dan menghubungkan ke internet dengan DHCP
void LANS() {
  Serial.println("Menghubungkan ke LAN");
  Ethernet.init(2);

  if (Ethernet.begin(mac) == 1) {
    Serial.println("Terhubung ke LAN");
  }
}

//Fungsi loop untuk ethernet
void LANCheck() {
  LANS();
  if (Ethernet.linkStatus() != LinkON) {

    //Setup koneksi ethernet
    LANS();

    Serial.println("Kabel LAN tidak terhubung");

    //Setup NTP
    NTPS();

    delay(5000);
    loop();
  }

  else {
    //Fungsi loop untuk NTP
    NTPL();

    //Fungsi loop untuk Telegram
    TeleL();
  }
}