// Arduino Version 1.6.9
// platformio lib install VirtualWire
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
    Serial.println();
    // Serial.println(readString);

    // Inicio
    String param1 = "a";
    readValueHTTP(param1);
    Serial.println(param1);
    // Fin

    // Inicio
    String param2 = "b";
    readValueHTTP(param2);
    Serial.println(param2);
    // Fin

    if (param1 == "1") {
      digitalWrite(actuador1, HIGH);
    } else if (param1 == "0") {
      digitalWrite(actuador1, LOW);
    }

    if (param2 == "1") {
      digitalWrite(actuador2, HIGH);
    } else if (param2 == "0") {
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
