#ifndef RADIO_H
#define RADIO_H

#include <RF24.h>

//===----------------------------------------------------------------------===//
// Globais
//===----------------------------------------------------------------------===//

/**
 * Classe de comunicação com módulo RF24
 */
extern RF24 radio;

//===----------------------------------------------------------------------===//
// Definição de Endereço do PIPE
//===----------------------------------------------------------------------===//

// Esse endereço pode ser entendido melhor lendo o datasheet
#define PIPE_ADDRESS 0x3030303030LL

//===----------------------------------------------------------------------===//
// Definição da Pinagem do Módulo RF24
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
// Definição do Canal de Comunicação
//===----------------------------------------------------------------------===//

#define RADIO_CHANNEL 100

//===----------------------------------------------------------------------===//
// Funções Públicas
//===----------------------------------------------------------------------===//

/**
 * Inicializa a classe radio
 */
void init_radio();

#endif // RADIO_H
