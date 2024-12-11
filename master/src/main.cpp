#include <SPI.h>
#include "RF24.h"
#include "config.h"

// Instância o object para o nRF24L01 transmissor
RF24 radio(CE_PIN, CSN_PIN);

// Pipe que define os endereços de leitura e escrita
const uint64_t address[2] = {PIPE_ADDRESS, PIPE_ADDRESS};

char payloadT[5] = "test\n";
char payloadR[5];

void init_radio()
{
  // Inicializa o rádio e verifica se o mesmo está funcionando corretamente
  if (!radio.begin())
  {
    Serial.println(F("Radio não está respondendo!"));
    while (true)
    {
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
  radio.setDataRate(RF24_1MBPS);

  // Define o tamanho do payload para o rádio
  radio.setPayloadSize(sizeof(payloadT));

  // Abre um canal de escrita com o endereço especifíco
  radio.openWritingPipe(address[0]);

  // Abre um canal de leitura com o endereço especifíco
  radio.openReadingPipe(1, address[1]);

  // Define o canal inicial de comunicação do rádio
  radio.setChannel(110);

  // Imprime detalhes de configuração do rádio
  radio.printPrettyDetails();

  // Limpa o buffer de recepção (RX)
  radio.flush_rx();
}

bool receive_message()
{
  uint8_t packet[32];

  radio.startListening();
  delay(70);
  radio.read(&packet[0], 32);
  radio.stopListening();

  Serial.println(packet[0], HEX);

  radio.flush_rx();

  return true;
}

bool send_message(char *data, uint8_t size, uint8_t destiny)
{
  uint8_t packet[32];
  packet[0] = 213;
  packet[1] = destiny;
  packet[2] = NETWORK_ADDR;
  packet[31] = '\0';

  Serial.println(packet[0], HEX);

  radio.write(&packet[0], 32);
  radio.flush_tx();

  return true;
}

// bool enviaTrem(char *pacote, uint8_t tamanho, uint8_t destino)
// {
//   pacote[0] = destino;
//   pacote[1] = MASTER_ADDR;
//   char pacoteR[3];
//   bool enviou = false;
//   unsigned long start_timer = micros(); // start the timer
//   while (micros() - start_timer < TIMEOUT_SEND)
//   {
//     radio.startListening();
//     delayMicroseconds(70);
//     radio.stopListening();
//     if (!radio.testCarrier())
//     {
//       radio.write(&pacote[0], tamanho);
//       enviou = true;
//       Serial.println("E");
//       break;
//     }
//     else
//     {
//       Serial.println("O");
//       delayMicroseconds(150);
//     }
//   }
//   if (!enviou)
//   {
//     return false;
//   }
//   unsigned long start_timer_ack = micros();
//   radio.startListening();
//   while (micros() - start_timer_ack < TIMEOUT_ACK)
//   {
//     if (radio.available())
//     {
//       radio.read(&pacoteR[0], 3);
//       if (pacoteR[0] == MASTER_ADDR && pacoteR[1] == destino && pacoteR[2] == ACK)
//       {
//         unsigned long end_timer = micros();    // end the timer
//         Serial.print(end_timer - start_timer); // print the timer result

//         return true;
//       }
//       radio.flush_rx();
//     }
//   }
//   return false;
// }

// bool recebeTrem(char *pacote, uint8_t tamanho, int TIMEOUT)
// {
//   unsigned long start_timer = micros(); // start the timer
//   bool recebeu = false;
//   bool enviou = false;
//   radio.startListening();
//   while (micros() - start_timer < TIMEOUT)
//   {
//     if (radio.available())
//     {
//       radio.read(&pacote[0], tamanho);
//       if (pacote[0] == MASTER_ADDR)
//       {
//         recebeu = true;
//         Serial.println("R");
//         break;
//       }
//       radio.flush_rx();
//     }
//   }
//   radio.flush_rx();
//   if (!recebeu)
//   {
//     return false;
//   }
//   char pacoteACK[3];
//   pacoteACK[0] = pacote[1];
//   pacoteACK[1] = MASTER_ADDR;
//   pacoteACK[2] = ACK;
//   start_timer = micros(); // start the timer

//   while (micros() - start_timer < TIMEOUT_ACK)
//   {
//     radio.startListening();
//     delayMicroseconds(70);
//     radio.stopListening();
//     if (!radio.testCarrier())
//     {
//       radio.write(&pacoteACK[0], 3);
//       Serial.print(int(pacoteACK[0]));
//       Serial.print(int(pacoteACK[1]));
//       Serial.println(int(pacoteACK[2]));
//       enviou = true;
//       Serial.println("E");
//       break;
//     }
//     else
//     {
//       delayMicroseconds(100);
//     }
//   }
//   if (!enviou)
//   {
//     return false;
//   }
//   else
//   {
//     return true;
//   }
// }

void setup(void)
{
  Serial.begin(115200);
  init_radio();
}

bool send = false;

void loop(void)
{
  char data[] = "Print";
  send_message(data, 6, WORKER_LED_ADDR);
  delay(500);
  send = true;
}