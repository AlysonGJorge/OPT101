/**
 * Definição das principais configurações do sistema
 */
#ifndef CONFIG_H
#define CONFIG_H

//===----------------------------------------------------------------------===//
// Flags do protocolos
//===----------------------------------------------------------------------===//

/**
 * Acknowledge.
 *
 * Usado para reconhecer que a mensagem chegou até o destino
 */
#define ACK 0

/**
 * Clear to Send.
 *
 * Diz aos nós da rede que está livre para receber mensagens.
 */
#define CTS 1

/**
 * Request to Send.
 *
 * Diz aos nós da rede que deseja enviar uma mensagem.
 */
#define RTS 2

/**
 * Data.
 *
 * Diz ao nó que o pacote atual tem dados que podem ser interpretados..
 */
#define DTA 3

//===----------------------------------------------------------------------===//
// Endereço do Pipe
//===----------------------------------------------------------------------===//

// Esse endereço pode ser entendido melhor lendo o datasheet
#define PIPE_ADDRESS 0x3030303030LL

//===----------------------------------------------------------------------===//
// Pinagem do Módulo RF24
//===----------------------------------------------------------------------===//

/**
 * Chip Enable Pin.
 *
 * Usado para habilitar ou desabilitar os módulos de comunicação do rádio.
 */
#define CE_PIN 7

/**
 * Chip Select Not Pin.
 *
 * Usado para selecionar o módulo de comunicação. Quando este está em low, fala
 * para o módulo ouvir comandos do Arduino. Quando está high, o módulo está
 * desselecionado o Arduino pode se comunicar com outros dispositivos.
 */
#define CSN_PIN 8

//===----------------------------------------------------------------------===//
// Definições de Tempo
//===----------------------------------------------------------------------===//

/**
 * Tempo limite para verificação de envio
 */
#define TIMEOUT_SEND 2000

/**
 * Tempo limite para verificação do ACK
 */
#define TIMEOUT_ACK 2000

//===----------------------------------------------------------------------===//
// Definições da REDE
//===----------------------------------------------------------------------===//

/**
 * Endereço da rede
 */
#define NETWORK_ADDR 215

/**
 * Endereço do nó master
 */
#define MASTER_ADDR 1

/**
 * Endereço do nó worker led
 */
#define WORKER_LED_ADDR 2

/**
 * Endereço do nó worker sensor
 */
#define WORKER_SENSOR_ADDR 3

//===----------------------------------------------------------------------===//
// Definições do Pacote
//===----------------------------------------------------------------------===//
//
/**
 * Tamanho do pacote
 */
#define PACKET_SIZE 32

#endif // CONFIG_H
