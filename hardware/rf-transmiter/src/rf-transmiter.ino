// Se instaló con:
// platformio lib search VirtualWire
// platformio lib install VirtualWire
// // The digital IO pin number of the press to talk, enables the transmitter
// hardware
// static uint8_t vw_ptt_pin = 10;
// // The digital IO pin number of the receiver data
// static uint8_t vw_rx_pin = 11;
// // The digital IO pin number of the transmitter data
// static uint8_t vw_tx_pin = 12;
#include <VirtualWire.h>

char *estado = "0";
void setup() {
  Serial.begin(9600);
  Serial.println("El dispositivo esta listo.");
  // Initialize the IO and ISR
  vw_setup(200); // Bits per sec
}

void loop() {
  // Se debe encender Dispositivo
  if (estado == "0") {
    estado = "1";
  } else {
    estado = "0";
  }

  // Serial.println(estado);
  char dato[7] = "";
  strcat(dato, "a=0&b=");
  strcat(dato, estado);

  Serial.println(dato);
  send(dato);
  // Se debe apagar dispositivo (Pin Salida Digital de Control?)
  delay(1000);
}

void send(char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
