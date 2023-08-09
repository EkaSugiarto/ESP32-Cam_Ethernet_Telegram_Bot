/*
Bagian ini digunakan untuk mengambil epoc time dari internet
melalui Network Time Protocol (NTP), sudah disesuaikan untuk
waktu GMT+7
*/

#include <EthernetUdp.h>
#include <NTPClient.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset = 25200;
const int daylightOffset = 3600;
int hr, mi, sec;
String date, timee;

EthernetUDP ntpUDP;

NTPClient waktu(ntpUDP, ntpServer, gmtOffset, daylightOffset);

void NTPS() {
  //Memulai NTP
  waktu.begin();
}

//Fungsi loop NTP
void NTPL() {
  waktu.update();

  String date_time = waktu.getFormattedDate();
  int index_date = date_time.indexOf("T");
  date = date_time.substring(0, index_date);

  //Menyimpan data waktu dalam bentuk string dengan format Jam:Menit:Detik
  timee = waktu.getFormattedTime();
}