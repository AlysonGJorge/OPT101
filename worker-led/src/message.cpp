#include "message.h"
#include "config.h"
#include "packet.h"
#include "print.h"
#include "radio.h"

#include <Arduino.h>
#include <HardwareSerial.h>

//===-----------------------------------------------------------------------===
// Definições
//===-----------------------------------------------------------------------===

// Define a mensagem que irá ser mostrada ao enviar.
#define MSG_SND(x) ((x) == ACK ? "SND/ACK" : "SND")

// Define a mensagem que irá ser mostrada ao receber.
#define MSG_RCV(x) ((x) == ACK ? "ACK" : "RCV")

//===-----------------------------------------------------------------------===
// Buffers
//===-----------------------------------------------------------------------===

// Pacote usado para enviar dados
static char packetT[PACKET_SIZE];

// Pacote usado para receber dados
static char packetR[PACKET_SIZE];

//===-----------------------------------------------------------------------===
// Funções Públicas
//===-----------------------------------------------------------------------===

bool send_msg(uint8_t destiny, uint8_t flag, uint8_t body) {
  create_packet(packetT, destiny, flag, body);

  bool send = false;
  uint64_t timer = micros();
  while (micros() - timer < TIMEOUT_SEND) {
    // Ouve o meio
    radio.startListening();
    delayMicroseconds(DELAY_RECV);
    radio.stopListening();

    // Se o meio estiver livre envia, caso contrário espera
    if (!radio.testCarrier()) {
      radio.write(packetT, PACKET_SIZE);
      send = true;
      debugPrintln(MSG_SND(packetT[PACKET_FLAG]));
      break;
    } else {
      debugPrintln("OCP");
      delayMicroseconds(DELAY_SEND);
    }
  }

  if (send && flag == DTA) {
    uint8_t tmp = 0;
    return receive_msg(WORKER_LED_ADDR, ACK, tmp);
  }

  return send;
}

bool receive_msg(uint8_t source, uint8_t flag, uint8_t &body) {
  bool received = false;

  uint64_t timer = micros();
  radio.startListening();
  while (micros() - timer < TIMEOUT_RECV) {
    radio.read(packetR, PACKET_SIZE);

    // Verifica se a mensagem recebida bate com os critérios
    if (packetR[PACKET_CHECKSUM] == checksum(packetR) &&
        packetR[PACKET_DESTINY] == WORKER_LED_ADDR &&
        packetR[PACKET_NETWORK] == NETWORK_ADDR &&
        packetR[PACKET_FLAG] == flag) {
      received = true;
      debugPrintln(MSG_RCV(packetR[PACKET_FLAG]));
      break;
    }

    radio.flush_rx();
  }

  // Pacotes do tipo DTA enviam um ACK e salva o corpo da mensagem
  if (received && flag == DTA) {
    body = packetR[PACKET_BODY];
    return send_msg(source, ACK, 0);
  }

  return received;
}
