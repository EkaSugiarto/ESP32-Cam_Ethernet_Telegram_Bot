# ESP32-Cam_Ethernet_Telegram_Bot
ESP32-Cam system for low-cost CCTV that connected to Telegram BOT using ethernet internet connection

An AI Thinker ESP32-Cam board with OV2640 camera sensor connected to W5500 Lite ethernet module

Thanks to this several tutorial/repositories:
- https://github.com/arhi/EthernetSPI2
- https://mischianti.org/2022/10/18/esp32-ethernet-w5500-with-plain-http-and-ssl-https/
- https://stackoverflow.com/questions/53036361/how-to-save-bitmap-using-ov7670-esp32-and-spiffs
- https://www.tutorialspoint.com/esp32_for_iot/esp32_for_iot_spiffs_storage.htm
- https://randomnerdtutorials.com/esp32-cam-take-photo-save-microsd-card/
- https://randomnerdtutorials.com/telegram-control-esp32-esp8266-nodemcu-outputs/

This code has features:
- Send photo and time from NTP to all user who have the Telegram BOT link
- Send photo to only several user who joined to Telegram Group with the BOT when a sensor pin triggered HIGH


Next interesting feature to improve:
- This cam can do live streaming
- Can change the view direction by phone
- Integrated with dedicated mobile/PC app or website
