#ifndef PACKET_H
#define PACKET_H

#include <Arduino.h>

//===----------------------------------------------------------------------===//
// Definições do Pacote
//===----------------------------------------------------------------------===//

/**
 * Tamanho do pacote
 */
#define PACKET_SIZE 7

/**
 * Posição do endereço de destino do pacote
 */
#define PACKET_DESTINY 0

/**
 * Posição do endereço de origem do pacote
 */
#define PACKET_SOURCE 1

/**
 * Posição da informação de rede do pacote
 */
#define PACKET_NETWORK 3

/**
 * Posição do dado de controle do pacote
 */
#define PACKET_FLAG 4

/**
 * Posição dos dados do pacote
 */
#define PACKET_BODY 5

/**
 * Posição do checksum do pacote
 */
#define PACKET_CHECKSUM 6

//===----------------------------------------------------------------------===//
// Funções Públicas
//===----------------------------------------------------------------------===//

/**
 * @brief Realiza o checksum de um pacote
 *
 * O algortimo utilizado o checksum é um simples xor de todos os elementos
 * dentro do pacote.
 *
 * @param packet Ponteiro para o pacote
 *
 * @return O valor do checksum do pacote
 */
char checksum(char *packet);

/**
 * @brief Inicializa os metadados do pacote
 *
 * Insere o cabeçalho e realiza o checksum do pacote.
 *
 * @param packet Ponteiro para o pacote
 * @param destiny Endereço de destino do pacote
 * @param flag Valor que especifica o tipo de pacote
 * @param body Dados do pacote
 */
void create_packet(char *packet, uint8_t destiny, uint8_t flag, uint8_t body);

#endif // PACKET_H