#include <UniversalTelegramBot.h>

//Token dari BOT yang digunakan
#define BOT_TOKEN "6503495044:AAH-zAmJefB2iBnjeJy1LT1pbp4kV5OWEjE"

const unsigned long BOT_MTBS = 1000;

//Variabel untuk menyimpan teks yang akan dikirim ke user yang menggunakan BOT
String pesan, chat_id, text, from_name;

//Deklarasi header dari BOT yang diberi nama "bot"
UniversalTelegramBot bot(BOT_TOKEN, client);

unsigned long bot_lasttime;

void KirimFoto();
void KirimFotoGrup();
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
    if (text == "/start@CCTV_TA_bot" || text == "/start") {
      pesan = "Welcome to TA CCTV bot, " + from_name + "!";
      bot.sendMessage(chat_id, pesan);
    }

    //Jika pesan yang dikirim adalah "/foto"
    if (text == "/foto@CCTV_TA_bot" || text == "/foto") {
      KirimFoto();
      //Menulis waktu dari server NTP saat foto dikirim
      text = "";
      pesan = "";
      pesan = timee;
      bot.sendMessage(chat_id, pesan);
    }

    //Jika pesan yang dikirim adalah "/5foto"
    if (text == "/5foto@CCTV_TA_bot" || text == "/5foto") {

      //Perulangan untuk mengirim 1 foto dan teks waktu server NTP saat ini sebanyak 5 kali
      for (int iii = 0; iii < 5; iii++) {
        KirimFoto();
        //Menulis waktu dari server NTP saat foto dikirim
        text = "";
        pesan = "";
        pesan = timee;
        bot.sendMessage(chat_id, pesan);
      }
    }

    //Jika pesan yang dikirim adalah "/jam"
    if (text == "/jam" || text == "/jam@CCTV_TA_bot") {

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

//Fungsi untuk mengirim foto hanya ke user yang masuk ke grup "CCTV TA Tele"
void KirimFoto() {
  TakePhoto();

  pesan = "";

  //Membuka file "foto.jpg" dengan mode READ
  file = SPIFFS.open("/foto.jpg", FILE_READ);

  //Mengecek keberadaan file "foto.jpg"
  if (!file) {
    pesan = "Foto gagal diambil\n";
  }

  if (!isMoreDataAvailable()) {
    KirimFoto();
  }

  //Mengirim teks ke user yang mengirim pesan tersebut
  // bot.sendMessage(chat_id, pesan);

  //Mengirim foto ke user yang mengirim pesan tersebut
  bot.sendPhotoByBinary(chat_id, "image/jpeg", file.size(),
                        isMoreDataAvailable,
                        getNextByte, nullptr, nullptr);

  //Menutup file
  file.close();
}

String chat_idd = "824519381";

void KirimFotoGrup() {
  TakePhoto();

  pesan = "";

  //Membuka file "foto.jpg" dengan mode READ
  file = SPIFFS.open("/foto.jpg", FILE_READ);

  //Mengecek keberadaan file "foto.jpg"
  if (!file) {
    pesan = "Foto gagal diambil\n";
  }

  if (!isMoreDataAvailable()) {
    KirimFotoGrup();
  }

  //Mengirim foto ke user yang mengirim pesan tersebut
  bot.sendPhotoByBinary(chat_idd, "image/jpeg", file.size(),
                        isMoreDataAvailable,
                        getNextByte, nullptr, nullptr);

  //Menutup file
  file.close();
}

//Fungsi untuk membaca nilai analog dari pin sensor.
//Jika pada detik kelipatan 10 nilai analog >= 4000, maka panggil fungsi KirimFoto2()
void SensorL() {
  if (waktu.getSeconds() % 10 == 0) {
    if (analogRead(Sensorpin >= 4000)) {
      KirimFotoGrup();
    }
  }
}