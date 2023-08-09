// #include <ArduinoJson.h>
// #include "WString.h"

// String temps, response;
// const char* responnya;

// StaticJsonDocument<2048> doc;

// void JSONParserL() {
//   // Inside the brackets, 200 is the capacity of the memory pool in bytes.
//   // Don't forget to change this value to match your JSON document.
//   // Use https://arduinojson.org/v6/assistant to compute the capacity.

//   DeserializationError error = deserializeJson(doc, response);

//   responnya = doc["ok"];
//   temps = String(responnya);
//   if (error){
//     temps += "Error"
//   }
// }