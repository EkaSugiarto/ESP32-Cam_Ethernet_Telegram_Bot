#include <UniversalTelegramBot.h>

//Token dari BOT yang digunakan
#define BOT_TOKEN "6502923709:AAH6WNSSOTMD2iuBSS8dlHl_WZAQ7Cn8ncI"

const unsigned long BOT_MTBS = 1000;

//Variabel untuk menyimpan teks yang akan dikirim ke user yang menggunakan BOT
String pesan, chat_id, text, from_name;

//Deklarasi header dari BOT yang diberi nama "bot"
UniversalTelegramBot bot(BOT_TOKEN, client);

unsigned long bot_lasttime;

void KirimFoto1();
void KirimFoto2();
void SensorL();
void TeleL();

//Mengecek apakah file foto.jpg di SPIFFS ada atau tidak
bool isMoreDataAvailable() {
  return file.available();
}

//Membaca file foto.jpg
byte getNextByte() {
  return file.read();
}

//Mengambil pesan yang dikirim oleh user ke chat BOT
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    chat_id = bot.messages[i].chat_id;
    text = bot.messages[i].text;
    from_name = bot.messages[i].from_name;

    //Jika nama user yg mengirim pesan tersebut tidak diketahui
    if (from_name == "")
      from_name = "Guest";

    //Jika pesan yang dikirim adalah "/start"
    if (text == "/start") {
      pesan = "Welcome to TA CCTV bot, " + from_name + "!";
      bot.sendMessage(chat_id, pesan);
    }

    //Jika pesan yang dikirim adalah "/foto"
    if (text == "/foto") {
      KirimFoto1();
    }

    //Jika pesan yang dikirim adalah "/5foto"
    if (text == "/5foto") {

      //Perulangan untuk mengirim 1 foto dan teks waktu server NTP saat ini sebanyak 5 kali
      for (int iii = 0; iii < 5; iii++) {
        KirimFoto1();
      }
    }

    //Jika pesan yang dikirim adalah "/jam"
    if (text == "/jam") {

      //Menulis waktu dari server NTP saat foto dikirim
      pesan = timee;

      //Mengirim teks ke user yang mengirim pesan tersebut
      bot.sendMessage(chat_id, pesan);
    }
  }
}

//Fungsi untuk mengecek apakah ada pesan masuk atau tidak ke chat BOT
void TeleL() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("Ada pesan masuk");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}

void KirimFoto1() {
  //Mengambil 1 frame foto dan membuat file "foto.jpg"
  LampuIROn();
  TakePhoto();

  pesan = "";

  //Membuka file "foto.jpg" dengan mode READ
  file = SPIFFS.open("/foto.jpg", FILE_READ);

  //Mengecek keberadaan file "foto.jpg"
  if (!file) {
    pesan = "Foto gagal diambil\n";
  }

  //Mengirim foto ke user yang mengirim pesan tersebut
  bot.sendPhotoByBinary(chat_id, "image/jpeg", file.size(),
                        isMoreDataAvailable,
                        getNextByte, nullptr, nullptr);

  //Menutup file
  file.close();

  //Menulis waktu dari server NTP saat foto dikirim
  pesan += timee;

  //Mengirim teks ke user yang mengirim pesan tersebut
  bot.sendMessage(chat_id, pesan);
  LampuIROff();
}

String chat_idd = "-824519381";

//Fungsi untuk mengirim foto hanya ke user yang masuk ke grup "CCTV TA Tele"
void KirimFoto2() {
  //Mengambil 1 frame foto dan membuat file "foto.jpg"
  LampuIROn();
  TakePhoto();

  pesan = "";

  //Membuka file "foto.jpg" dengan mode READ
  file = SPIFFS.open("/foto.jpg", FILE_READ);

  //Mengecek keberadaan file "foto.jpg"
  if (!file) {
    pesan = "Foto gagal diambil\n";
  }

  //Mengirim foto ke user yang mengirim pesan tersebut
  bot.sendPhotoByBinary(chat_idd, "image/jpeg", file.size(),
                        isMoreDataAvailable,
                        getNextByte, nullptr, nullptr);

  //Menutup file
  file.close();

  //Menulis waktu dari server NTP saat foto dikirim
  pesan += timee;

  //Mengirim teks ke user yang mengirim pesan tersebut
  bot.sendMessage(chat_id, pesan);
  LampuIROff();
}

//Fungsi untuk membaca nilai analog dari pin sensor.
//Jika pada detik kelipatan 10 nilai analog >= 4000, maka panggil fungsi KirimFoto2()
void SensorL() {
  if (waktu.getSeconds() % 10 == 0) {
    if (analogRead(Sensorpin >= 4000)) {
      KirimFoto2();
    }
  }
}