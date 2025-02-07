#include "packet.h"
#include "config.h"

char checksum(char *packet) {
  char check = 0x00;

  for (int i = 0; i < PACKET_SIZE - 1; i++) {
    check ^= packet[i];
  }

  return check;
}

void create_packet(char *packet, uint8_t destiny, uint8_t flag, uint8_t body) {
  packet[PACKET_DESTINY] = destiny;
  packet[PACKET_SOURCE] = WORKER_LED_ADDR;
  packet[PACKET_NETWORK] = NETWORK_ADDR;
  packet[PACKET_FLAG] = flag;
  packet[PACKET_BODY] = body;
  packet[PACKET_CHECKSUM] = checksum(packet);
}