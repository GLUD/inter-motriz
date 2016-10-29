// Arduino Version 1.6.9
// platformio lib install VirtualWire
// // The digital IO pin number of the press to talk, enables the transmitter
// hardware
// static uint8_t vw_ptt_pin = 10;
// // The digital IO pin number of the receiver data
// static uint8_t vw_rx_pin = 11;
// // The digital IO pin number of the transmitter data
// static uint8_t vw_tx_pin = 12;

#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
String readString = String(30);

const byte actuador1 = 8;
const byte actuador2 = 9;

void setup() {
  Serial.begin(9600);
  Serial.println("El dispositivo esta listo.");
  // Initialize the IO and ISR
  vw_setup(200); // Bits per sec
  vw_rx_start(); // Start the receiver

  pinMode(actuador1, OUTPUT);
  digitalWrite(actuador1, LOW);

  pinMode(actuador2, OUTPUT);
  digitalWrite(actuador2, LOW);
}

void loop() {
  if (vw_get_message(message, &messageLength)) { // Non-blocking
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
      readString += (char)message[i];
    }
    Serial.println(readString);

    if (readString == "0") {
      digitalWrite(actuador1, HIGH);
    } else if (readString == "1") {
      digitalWrite(actuador1, LOW);
    } else if (readString == "2") {
      digitalWrite(actuador2, HIGH);
    } else if (readString == "3") {
      digitalWrite(actuador2, LOW);
    }
  }
  readString = "";
}

// RFC 7231 - Hypertext Transfer Protocol (HTTP/1.1)
void readValueHTTP(String &keyParam) {
  String parametro = keyParam + "=";
  int indice = readString.indexOf(parametro);
  if (indice > -1) {
    keyParam = readString.substring(indice + parametro.length());
    int indice2 = keyParam.indexOf("&");
    if (indice2 > -1) {
      indice = indice2;
    }
    keyParam = keyParam.substring(0, indice);
  }
}
