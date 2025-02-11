#include "radio.h"
#include "packet.h"

// Instância o object para o nRF24L01 transmissor
RF24 radio(CE_PIN, CSN_PIN);

// Pipe que define os endereços de leitura e escrita
uint64_t address[2] = {PIPE_ADDRESS, PIPE_ADDRESS};

void init_radio() {
  // Inicializa o rádio e verifica se o mesmo está funcionando corretamente
  if (!radio.begin()) {
    Serial.println(F("Radio não está respondendo!"));
    while (true) {
    }
  }

  // Define o nível máximo de potência
  radio.setPALevel(RF24_PA_MAX);

  // Desativa o reconhecimento automático (auto ACK)
  radio.setAutoAck(false);

  // Desativa a verificação de redundância cíclica (CRC)
  radio.disableCRC();

  // Define a taxa de transmissão de dados. Neste caso a taxa de
  // transmissão é de 1 Mbps.
  radio.setDataRate(RF24_2MBPS);

  // Define o tamanho do payload para o rádio
  radio.setPayloadSize(sizeof(char) * PACKET_SIZE);

  // Abre um canal de escrita com o endereço especifíco
  radio.openWritingPipe(address[0]);

  // Abre um canal de leitura com o endereço especifíco
  radio.openReadingPipe(1, address[1]);

  // Define o canal inicial de comunicação do rádio
  radio.setChannel(100);

  // Imprime detalhes de configuração do rádio
  radio.printPrettyDetails();

  // Limpa o buffer de recepção (RX)
  radio.flush_rx();
}
